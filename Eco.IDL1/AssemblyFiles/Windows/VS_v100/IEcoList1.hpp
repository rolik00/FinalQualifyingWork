interface IEcoList1 : public IEcoUnknown {
public:
    /* IEcoList1 */
    virtual uint32_t ECOCALLMETHOD Count() = 0;
    virtual void* ECOCALLMETHOD Item(uint32_t index) = 0;
    virtual uint32_t ECOCALLMETHOD Add(void* value) = 0;
    virtual void ECOCALLMETHOD InsertAt(uint32_t index, void* value) = 0;
    virtual void ECOCALLMETHOD Remove(void* value) = 0;
    virtual void ECOCALLMETHOD RemoveAt(uint32_t index) = 0;
    virtual void ECOCALLMETHOD Clear() = 0;

}; 