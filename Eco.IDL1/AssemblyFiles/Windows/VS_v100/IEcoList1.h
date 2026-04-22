typedef struct IEcoList1* IEcoList1Ptr_t;

typedef struct IEcoList1VTbl {
    /* IEcoUnknown */
    int16_t (ECOCALLMETHOD *QueryInterface )(/* in */ IEcoList1Ptr_t me, /* in */ const UGUID* riid, /* out */ voidptr_t* ppv);
    uint32_t (ECOCALLMETHOD *AddRef )(/* in */ IEcoList1Ptr_t me);
    uint32_t (ECOCALLMETHOD *Release )(/* in */ IEcoList1Ptr_t me);
    /* IEcoList1 */
    uint32_t (ECOCALLMETHOD *Count)(/* in */ IEcoList1Ptr_t me);
    void* (ECOCALLMETHOD *Item)(/* in */ IEcoList1Ptr_t me, uint32_t index);
    uint32_t (ECOCALLMETHOD *Add)(/* in */ IEcoList1Ptr_t me, void* value);
    void (ECOCALLMETHOD *InsertAt)(/* in */ IEcoList1Ptr_t me, uint32_t index, void* value);
    void (ECOCALLMETHOD *Remove)(/* in */ IEcoList1Ptr_t me, void* value);
    void (ECOCALLMETHOD *RemoveAt)(/* in */ IEcoList1Ptr_t me, uint32_t index);
    void (ECOCALLMETHOD *Clear)(/* in */ IEcoList1Ptr_t me);

} IEcoList1VTbl;

interface IEcoList1 {
    struct IEcoList1VTbl *pVTbl;
} IEcoList1;
