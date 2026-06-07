extern ULONG g_dwDLLRefCount;

// **************************************************************************
// MedicalHistoryClassFactory
//
//  This is a simple implementation of a class which is used to instantiate
//  another class... specifically the MedicalHistoryMenuExtension COM class
//
//  This class is instantiated/constructed by DllGetClassObject (see Main.cpp)
//
class MedicalHistoryClassFactory : public IClassFactory
{
private:
    long m_cRef;

public:
    MedicalHistoryClassFactory();
    virtual ~MedicalHistoryClassFactory();

    // IUnknown interface
    STDMETHODIMP QueryInterface(REFIID riid, void** ppObject);

    STDMETHODIMP_(ULONG) AddRef(); 
    STDMETHODIMP_(ULONG) Release();

    STDMETHODIMP CreateInstance(IUnknown *pUnkOuter, REFIID riid, void** ppObject);
    STDMETHODIMP LockServer(BOOL fLock);
};
