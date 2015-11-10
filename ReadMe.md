#BaiduMapInMFC Project
This project embeds the Baidu map into a MFC(Microsoft Funcdation Classes) project.This makes it easy to explore a map,find a place,navigate and other ultilizations in a desktop application with C++ as same as a web application with Javascript.

As we all known,in a web application,it's easy to call the `web service` provided by a network address,for instance,Baidu Map web service is provided by http://api.map.baidu.com. However, **HOW TO CALL THE WEB SERVICE IN C++?** Unfortunately,we can't.But, it is practicable to call a Javascript function in c++,so we get an idea.Building in a Web Browser into a MFC application,so that the application can analysis Javascript and make a response to the event of the MFC UI.

First,let's have a look at the appearance of this project:
![](http://i.imgur.com/KdOfTs6.jpg)
Yes,so easy a desktop appliction!A Baidu Map centers in the capital of China and a Push Button on the bottom.When you push the button `ployLine`,the Message Handler of this button will call a Javascript function defined in a html file loaded when this application is created.Mouse wheel scrolling  to zoom in and out,mouse dragging to recenter are available.

**HOW TO DO!**
1. Create a MFC project based on dialog;
2. Clear all the existed controls in the UI;
3. Right click on the dialog to *`Insert Active X Control`*,select *`Microsoft Web Browser`* in the list of popup dialog;
4. A new control will be added on the UI,allocate a unique id *`IDC_EXPLORER1`* for it;
5. Right click on the *`IDC_EXPLORER1`* control in the UI,select *`Add Variables`* to add a variable for this control named *`m_explorer1`*.Two files *`explorer1.cpp`*,*`explorer1.h`* will be added to the project.Actully,this control is a Web browser like Internet Explorer,we build it in our appliction. 
6. In the member function *`OnInitDialog()`*, we need to load a html file for the Browser.The file *`map.html`* in the codes is in the project directory,it will access the Baidu Map web service and present a map in the Browser.
```c++
TCHAR strCurDir[512];
GetCurrentDirectory(sizeof(strCurDir), strCurDir);
m_web.Navigate((CString)strCurDir+_T("\\map.html"), NULL, NULL, NULL, NULL);
```
7. Now,build the project,a Baidu Map is embedded in the *`IDC_EXPLORER1`* control;
8. Next we need to call the Javascript functions defined in *`map.html`* to interact with the embedded Browser.
9. Add two files into this project,*`WebPage.cpp`*,*`WebPage.h`*.They are open source and provides the interface to access JS functions in C++;
10. Instantiate an object of clsses CWebPage,named *`m_web`*;
11. Add a Message Handler of the PushButton;
12. In the Message Handler,we try to call a JS function to draw some polyLines on the top level of the map:
```
void CBaiduMapInMFCDlg::OnBnClickedBtnPolyline()
{
	CWebPage page;
	page.SetDocument(m_web.GetDocument());
	CComVariant varResult;
	CString strLon, strLat;
	static int i = -1;
	if (++i >= m_pos.size())
		i = 0;
	strLon.Format(_T("%f"), m_pos[i].lon);
	strLat.Format(_T("%f"), m_pos[i].lat);
	page.CallJScript(_T("onDrawLine"), (const CString)strLon, (const CString)strLat, &varResult);
}
```
m_pos is a vector,and stores some predefined lontitude and latitude pairs read from file *`data/pos.txt`*
13. Now, push the button *`polyLine`*, some polyLines will be drew on the map.