DMDOC.H
OnUpdateSelectColor has been made public so that CMainFrame can call it.
Once OnInitMenuPopup bug is fixed, make it protected.

DMDOC.CPP
OnUpdateSelectColor currently gets menu and checks it.
Once CCmdUI bug is fixed, change this back to ->SetCheck....

OnSelectColor currently calls OnUpdateSelectColor for each color option.
Once OnInitMenuPopup bug fixed, remove this code.

MAINFRM.CPP
Once GetMenu() bug is fixed, get rid of Attach and Detach.

RefreshColorMenu calls OnUpdateSelectColor manually
On OnInitMenuPopup bug fixed, remove this code.
