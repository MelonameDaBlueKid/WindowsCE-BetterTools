#ifndef __CEFRTL_H__
#define __CEFRTL_H__

extern "C" 
{
	struct dispCallInfo 
	{
		UINT nAlignStack;	// usually 4
		UINT nAlignDoubles;	// usually 4
		UINT nShadowDoubles;// usually 0	
		UINT nScratchSize;	// usually 0
		int  nStackOffset;	// usually 0
		UINT nStackMin;		// usually 0
		BOOL bRetValFirst;	// usually FALSE
	};

	void helper__GetDispCallInfo(dispCallInfo* pInfo);

#if !defined(NO_DISPCALL_PROTOTYPE)
	DWORD helper__AfxDispatchCall(DWORD /*pfn*/, void* /*pArgs*/, UINT /*nSizeArgs*/);
	DWORD helper__AtlceDispatchCall(DWORD /*pfn*/, void* /*pArgs*/, UINT /*nSizeArgs*/);
#endif // NO_CALLDISP_PROTOTYPE

	// Note: pNewProc and pOldProc are out parameters and are optional (pass NULL)
	DWORD helper__CreateAtlceThunk(HWND hWnd, WNDPROC atlceProc, void* pThis, 
                                   BOOL bDlgProc, WNDPROC* pNewProc, WNDPROC* pOldProc);
	void helper__DeleteAtlceThunk(DWORD dwThunkHandle);

	size_t helper__GetJumpBufSize();

} // extern "C"

#endif // __CEFRTL_H__



