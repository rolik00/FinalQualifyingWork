@EcoNative
 public interface IEcoList1 extends IEcoUnknown {
    int Count();
    void* Item(int index);
    int Add(void* value);
    void InsertAt(int index, void* value);
    void Remove(void* value);
    void RemoveAt(int index);
    void Clear();

}
