# Архитектура Системы Синтаксического Анализа (Eco Parser PDA)
## 1. Обзор системы (High-Level Design)
Архитектура построена на разделении процесса на две фазы: Генерация таблиц (Static) и Исполнение (Runtime). В качестве исполнительного механизма используется универсальный магазинный автомат (PDA), что позволяет реализовать алгоритмы LL(k), SLR и LR(k).
Основные компоненты:

    IEcoBNF1: Представление входной грамматики в форме Бэкуса-Наура.
    IEcoParser1LRk (CEcoLR1): Компонент-генератор. Вычисляет множества FIRST/FOLLOW, строит каноническую коллекцию пунктов (Item Sets) и формирует граф переходов.
    IEcoPDA1: Инфраструктура магазинного автомата. Предоставляет стек и механизм переходов (FSM + Stack Operations).
    IEcoParser1ActionProcessing: Исполнитель (Driver). Связывает поток входных токенов с PDA и выполняет операции переноса (Shift) и свертки (Reduce).

## 2. Иерархия компонентов (Component Diagram)
```mermaid

graph TD
    User([Приложение]) --> LRk[IEcoParser1LRk]
    LRk --> BNF[IEcoBNF1]
    LRk --> PDA[IEcoPDA1]
    
    User --> Proc[IEcoParser1ActionProcessing]
    Proc --> PDA_Proc[IEcoPDA1EventProcessing]
    PDA_Proc --> Stack[IEcoStack1]
    PDA_Proc --> FSM[IEcoFSM1StateMachine]

```
## 3. Модель Данных Детерминированной Конфигурации (ДК)
Для реализации LR-парсинга на PDA используется один стек, в котором хранятся идентификаторы состояний:

    Состояние ДК: Пара (S, Stack), где S — текущее состояние FSM, Stack — история переходов.
    SHIFT (Перенос): Push(TargetStateID) в стек PDA + переход FSM в TargetState.
    REDUCE (Свертка): Pop(LengthOfRule) из стека PDA + GOTO переход по нетерминалу.

## 4. Диаграмма последовательности: Инициализация (InitByGrammar)
Этот процесс описывает, как грамматика BNF превращается в настроенный PDA.
```mermaid

sequenceDiagram
    participant App as Приложение
    participant LRk as CEcoLR1
    participant BNF as IEcoBNF1
    participant PDA as IEcoPDA1
    
    App->>LRk: InitByGrammar(pIGrammar)
    LRk->>BNF: get_RuleList()
    LRk->>LRk: BuildFirst() / BuildFollow()
    LRk->>LRk: BuildItemSets()
    
    LRk->>PDA: get_FSM()
    PDA-->>LRk: pIStateMachine
    
    loop По всем ItemSets
        LRk->>PDA: SetStackOpBySymbol(pTrans, SHIFT_DATA)
    end
    
    LRk-->>App: Result (Ready to Parse)
```

## 5. Диаграмма последовательности: Такт анализа (InvokeById)
Процесс обработки входного токена (например, терминала 'a').
```mermaid

sequenceDiagram
    participant App as Приложение
    participant AP as ActionProcessing
    participant PDA as IEcoPDA1EventProcessing
    
    App->>AP: InvokeById(TokenID)
    AP->>PDA: InvokeById(TokenID)
    
    Note over PDA: PDA выполняет SHIFT:<br/>1. Переход FSM<br/>2. Push(StateID) в стек
    
    PDA-->>AP: pNextState
    
    alt Если действие REDUCE
        AP->>AP: Get Rule Length (N)
        loop N раз
            AP->>PDA: PopSymbol()
        end
        AP->>PDA: InvokeByName(NonTerminalName)
        Note over PDA: Выполнение GOTO
    end
    
    AP-->>App: IEcoParser1Action (Status)

```
## 6. Ключевые проектные решения (C89 Compliance)

    Управление памятью: Все структуры EcoPDA1StackOp аллоцируются в куче (m_pIMem->Alloc) при построении таблиц, так как время жизни конфигурации превышает время жизни функции инициализации.
    Слабые ссылки: Геттеры (например, get_Grammar) возвращают указатели без автоматического AddRef. Пользователь (или вызывающий компонент) обязан делать AddRef, если планирует хранить указатель долго.
    Инкапсуляция: PDA не знает о BNF-правилах. Он лишь выполняет команды Pop(N) и Push(Symbol). Вся высокоуровневая логика (какое именно правило сработало) инкапсулирована в ActionProcessing.