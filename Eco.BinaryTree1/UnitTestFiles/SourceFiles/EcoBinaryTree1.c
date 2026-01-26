/*
 * <кодировка символов>
 *   Cyrillic (UTF-8 with signature) - Codepage 65001
 * </кодировка символов>
 *
 * <сводка>
 *   EcoBinaryTree1
 * </сводка>
 *
 * <описание>
 *   Данный исходный файл является точкой входа
 * </описание>
 *
 * <автор>
 *   Copyright (c) 2018 Vladimir Bashev. All rights reserved.
 * </автор>
 *
 */

/* Eco OS */
#include "IEcoSystem1.h"
#include "IdEcoMemoryManager1.h"
#include "IdEcoInterfaceBus1.h"
#include "IdEcoFileSystemManagement1.h"
#include "IdEcoBinaryTree1.h"
#include <windows.h>

#define MAX_LEN 10

#ifdef _WIN32
void set_console_color(WORD color) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
}

void reset_console_color() {
    set_console_color(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
}
#endif

/* Вспомогательная функция для проверки условий теста */
void TestAssert(boolean condition, char* msg) {
    if (condition) { 
		#ifdef _WIN32
		set_console_color(FOREGROUND_GREEN);
        printf("[%cTEST PASSED] %s\n", 251, msg);
		reset_console_color();
        #endif
    } else { 
		#ifdef _WIN32
		set_console_color(FOREGROUND_RED);
        printf("[%cTEST FAILED] %s\n", 120, msg);
		reset_console_color();
        #endif
    }
}

/* Вспомогательная функция поиска высоты дерева */
int tree_height(IEcoBinaryTree1Node* node) {
	int left_height = 0, right_height = 0;

    if (node == 0) return 0;
    
    left_height = tree_height(node->pVTbl->get_Left(node));
    right_height = tree_height(node->pVTbl->get_Right(node));
    
    return (left_height > right_height ? left_height : right_height) + 1;
}

char* emptySpace(int n) {
    int i = 0, len = n * MAX_LEN;
    char* spaces = (char*)malloc(len + 1);
    for (i = 0; i < len; i++) {
        spaces[i] = ' ';
    }
    spaces[len] = '\0';
    return spaces;
}

/* Вспомогательная функция для вывода дерева в консоль */ 
void PrintTree(IEcoBinaryTree1Node* node) {
	IEcoBinaryTree1Node* queue[100];
    int front = 0, rear = 0, n = tree_height(node), level_size = 0, i = 0;
    char* space = "";

    if (node == 0) return;
    

    queue[rear++] = node;
    
    while (front < rear) {
        level_size = rear - front;
        
        for (i = 0; i < level_size; i++) {
            IEcoBinaryTree1Node* current = queue[front++];
            
            if (space != "") {
                printf("%s%s%s", emptySpace(n), space, emptySpace(1));
                space = "";
            }
			printf("%s%s%s", emptySpace(n), current->pVTbl->get_Name(current), emptySpace(1));
            
            if (current->pVTbl->get_Left(current) != 0) {
                queue[rear++] = current->pVTbl->get_Left(current);
            }
			if (current->pVTbl->get_Right(current) != 0) {
                if (current->pVTbl->get_Left(current) == 0) space = emptySpace(1); 
                queue[rear++] = current->pVTbl->get_Right(current);
            }
            
            n--;
        }
        printf("\n");
    }
}

/*
 *
 * <сводка>
 *   Функция EcoMain
 * </сводка>
 *
 * <описание>
 *   Функция EcoMain - точка входа
 * </описание>
 *
 */
int16_t EcoMain(IEcoUnknown* pIUnk) {
    int16_t result = -1;
    /* Указатель на системный интерфейс */
    IEcoSystem1* pISys = 0;
    /* Указатель на интерфейс работы с системной интерфейсной шиной */
    IEcoInterfaceBus1* pIBus = 0;
    /* Указатель на интерфейс работы с памятью */
    IEcoMemoryAllocator1* pIMem = 0;
	char_t* name = 0;
    
	IEcoBinaryTree1* pTree = 0;
    IEcoBinaryTree1Node* pRoot = 0;
    IEcoBinaryTree1Node* pLeft = 0;
    IEcoBinaryTree1Node* pRight = 0;
    IEcoBinaryTree1Node* pGrandChild = 0;
    IEcoBinaryTree1Node* pFailNode = 0;
    char_t* nameCheck = 0;

    /* Проверка и создание системного интрефейса */
    if (pISys == 0) {
        result = pIUnk->pVTbl->QueryInterface(pIUnk, &GID_IEcoSystem, (void **)&pISys);
        if (result != 0 && pISys == 0) {
        /* Освобождение системного интерфейса в случае ошибки */
            goto Release;
        }
    }

    /* Получение интерфейса для работы с интерфейсной шиной */
    result = pISys->pVTbl->QueryInterface(pISys, &IID_IEcoInterfaceBus1, (void **)&pIBus);
    if (result != 0 || pIBus == 0) {
        /* Освобождение в случае ошибки */
        goto Release;
    }
#ifdef ECO_LIB
    /* Регистрация статического компонента для работы со списком */
    result = pIBus->pVTbl->RegisterComponent(pIBus, &CID_EcoBinaryTree1, (IEcoUnknown*)GetIEcoComponentFactoryPtr_7CAD4D0215EF4EDFB1FF6A7CAF1C3D6C);
    if (result != 0 ) {
        /* Освобождение в случае ошибки */
        goto Release;
    }
#endif
    /* Получение интерфейса управления памятью */
    result = pIBus->pVTbl->QueryComponent(pIBus, &CID_EcoMemoryManager1, 0, &IID_IEcoMemoryAllocator1, (void**) &pIMem);

    /* Проверка */
    if (result != 0 || pIMem == 0) {
        /* Освобождение системного интерфейса в случае ошибки */
        goto Release;
    }

    /* Выделение блока памяти */
    name = (char_t *)pIMem->pVTbl->Alloc(pIMem, 10);

    /* Заполнение блока памяти */
    pIMem->pVTbl->Fill(pIMem, name, 'a', 9);

    /* Получение тестируемого интерфейса */
    result = pIBus->pVTbl->QueryComponent(pIBus, &CID_EcoBinaryTree1, 0, &IID_IEcoBinaryTree1, (void**) &pTree);
    if (result != 0 || pTree == 0) {
        /* Освобождение интерфейсов в случае ошибки */
        goto Release;
    }
	
	printf("========================================\n");
    printf("   STARTING UNIT TESTS: EcoBinaryTree1  \n");
    printf("========================================\n");

	/* ТЕСТ: Создание корня */
    printf("\nTEST: Creating Root\n");
    pRoot = pTree->pVTbl->CreateNode(pTree, 0, "Root");
    TestAssert(pRoot != 0, "CreateNode(Root)");

	/* ТЕСТ: Вставка левого ребенка */
    printf("\nTEST: Inserting Left Child from InsertNodeByData()\n");
    pLeft = pTree->pVTbl->InsertNodeByData(pTree, pRoot, 0, "Left");
    TestAssert((pLeft != 0 && pRoot->pVTbl->get_Left(pRoot) == pLeft), "InsertNodeByData(Left)");

	/* ТЕСТ: Вставка правого ребенка (через создание узла + InsertNode) */
    printf("\n[TEST] Inserting Right Child from CreateNode() + InsertNode()\n");
    pRight = pTree->pVTbl->CreateNode(pTree, 0, "Right");
    if (pRight) {
        IEcoBinaryTree1Node* res = pTree->pVTbl->InsertNode(pTree, pRoot, pRight);
        TestAssert((res != 0 && pRoot->pVTbl->get_Right(pRoot) == res), "InsertNode(Right)");
    }

	/* ТЕСТ: Вставка внука */
    printf("\n[TEST] Inserting Grandchild to Left\n");
    pGrandChild = pTree->pVTbl->InsertNodeByData(pTree, pLeft, 0, "GrandChild");
	TestAssert((pGrandChild != 0 && pLeft->pVTbl->get_Left(pLeft) == pGrandChild), "InsertNodeByData(GrandChild)");

	/* ТЕСТ: Проверка на бинарность (Попытка добавить 3-го ребенка) */
    printf("\n[TEST] Checking Binary Constraint (Adding 3rd child to Root)\n");
    pFailNode = pTree->pVTbl->InsertNodeByData(pTree, pRoot, 0, "ExtraChild");
    if (pFailNode == 0) {
        TestAssert(1, "Tree successfully rejected 3rd child (Correct)");
    } else {
        TestAssert(0, "Tree FAILED constraint check (Accepted 3rd child!)");
        pFailNode->pVTbl->Release(pFailNode);
    }

	/* Визуализация */
    printf("\n--- Visual Tree Structure ---\n");
    PrintTree(pRoot);
    printf("-----------------------------\n");

	/* ТЕСТ: Удаление поддерева */
    printf("\n[TEST] Deleting Left Child (and its subtree)...\n");
    result = pTree->pVTbl->DeleteNode(pTree, pLeft);
    TestAssert((result > 0 && pRoot->pVTbl->get_Left(pRoot) == 0), "DeleteNode(Left)");
    
    pLeft = 0;
    pGrandChild = 0;

	/* Визуализация дерева после удаления */
    printf("\n--- Tree After Deletion ---\n");
    PrintTree(pRoot);

	/* ТЕСТ: Очистка */
    printf("\n[TEST] Clearing Tree...\n");
    result = pTree->pVTbl->Clear(pTree);
    TestAssert(result == 0, "Clear()");
    pRoot = 0;
    pRight = 0;

    printf("\n========================================\n");
    printf("    TESTS FINISHED\n");
    printf("========================================\n");

    /* Освобождение блока памяти */
    pIMem->pVTbl->Free(pIMem, name);

Release:

    /* Освобождение интерфейса для работы с интерфейсной шиной */
    if (pIBus != 0) {
        pIBus->pVTbl->Release(pIBus);
    }

    /* Освобождение интерфейса работы с памятью */
    if (pIMem != 0) {
        pIMem->pVTbl->Release(pIMem);
    }

    /* Освобождение тестируемого интерфейса */
    if (pTree != 0) {
        pTree->pVTbl->Release(pTree);
    }


    /* Освобождение системного интерфейса */
    if (pISys != 0) {
        pISys->pVTbl->Release(pISys);
    }

    return result;
}
