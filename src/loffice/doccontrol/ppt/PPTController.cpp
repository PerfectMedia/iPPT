/*
 * PPTController.cpp
 *
 *  Created on: Jul 9, 2011
 *      Author: mordonez
 */

#include "PPTController.hpp"

Reference<XInterface> xInterface;
Reference<XComponentContext> xComponentContext;
OUString sService;
Reference<XComponent> xComponent;
Reference<XComponentLoader>xComponentLoader;
Reference<XSpreadsheet> xSheet;
Reference<XSpreadsheetDocument> xSheetDocument;
Reference<XMultiComponentFactory> xMultiComponentFactoryClient;

PPTController::PPTController()
{
	cout << "PPTController" << endl;
}

//REEMPLAZAR POR boost para hacerlo cross platform
string PPTController::getCurrentDir()
{
	char buffer[512];

	string cur_dir = string(getcwd( buffer, -1 ));

	return cur_dir;
}
void PPTController::connect()
{
	//create a OUString to connect to the local host
	OUString sConnectionString = OUString::createFromAscii("uno:socket,host=localhost,port=8100;urp;StarOffice.ServiceManager");

	//create an instance of XSimpleRegistry...
	Reference< XSimpleRegistry > xSimpleRegistry(
	        createSimpleRegistry() );

	char buffer[512];

	string registry = getCurrentDir()+"/src/iPPT.rdb";

	cout << registry << endl;

	// ... and connect it to the registry file: iPPT.rdb, current directory
	OUString sRdbFile=OUString::createFromAscii(registry.c_str());
	try
	{
		xSimpleRegistry->open(sRdbFile,sal_True,sal_False);
	}
	catch (InvalidRegistryException e)
	{
		 OString o = OUStringToOString( e.Message, RTL_TEXTENCODING_ASCII_US );
		 printf( "An error occurred: %s\n", o.pData->buffer );
	}



	//open an  XComponentContext based on the registry file in
	// xSimpleRegistry
	xComponentContext = bootstrap_InitialComponentContext(xSimpleRegistry);

	//build the client-side service factory
	xMultiComponentFactoryClient = (xComponentContext->getServiceManager());

	//create an XInterface of the service factory, relying on the service string
	//and on the context; then...
	sService= OUString::createFromAscii
	( "com.sun.star.bridge.UnoUrlResolver" );

	xInterface=
	xMultiComponentFactoryClient->createInstanceWithContext
	(sService,xComponentContext);

	//...query it to build an XUnoUrlResolver interface and...
	Reference<XUnoUrlResolver> resolver(xInterface,UNO_QUERY);

	//...use its resolve() method to reach the openOffice server and to
	//create an XInterface to the server

	try
	   {
	    xInterface=Reference<XInterface>(resolver->resolve(sConnectionString),UNO_QUERY);
	   }
	catch(...)
	   {
	   printf("Error: could not connect to the server");
	   exit(1);
	   }
}

void PPTController::openDoc()
{
	//acquire the server-side context
	Reference<XPropertySet> xPropSet( xInterface, UNO_QUERY );
	OUString sProperty=OUString::createFromAscii("DefaultContext");
	xPropSet->getPropertyValue(sProperty) >>= xComponentContext;

	//take the OpenOffice service manager
	Reference<XMultiComponentFactory> xMultiComponentFactoryServer
	(xComponentContext->getServiceManager());

	//instantiate the component supporting the desired service
	//(load a document)
	sService=OUString::createFromAscii("com.sun.star.frame.Desktop");
	xInterface=xMultiComponentFactoryServer->createInstanceWithContext
	(sService,xComponentContext);
	Reference<XComponentLoader>xComponentLoader
	(xInterface,UNO_QUERY);

	xComponentLoader = xComponentLoader;

	//declare 3 OUString, to store URL, working directory
	//and name of the document
	OUString sDocUrl, sWorkingDir,sName;

	//find the working directory and write it
	osl_getProcessWorkingDir(&sWorkingDir.pData);


	string file = "src/presentacion.odp";

	//write the name of the document
	sName= OUString::createFromAscii(file.c_str());

	//create the URL
	osl::FileBase::getAbsoluteFileURL( sWorkingDir,sName,sDocUrl);

	//set the document type
	OUString sType=OUString::createFromAscii("_blank");

	try
	{
		//try to open the document
		xComponent=
		xComponentLoader->loadComponentFromURL
		(sDocUrl,sType,0,Sequence<PropertyValue>());
	}
	catch(IllegalArgumentException e)
	{
		 OString o = OUStringToOString( e.Message, RTL_TEXTENCODING_ASCII_US );
		 printf( "An error occurred: %s\n", o.pData->buffer );
	}

}

void ChangeTitle(const Reference< XDrawPagesSupplier > oDoc)
{
        Reference< ::com::sun::star::document::XDocumentInfoSupplier> infosupplier( oDoc, UNO_QUERY );
        Reference< ::com::sun::star::document::XDocumentInfo> docinfo = infosupplier->getDocumentInfo();
        Reference< XPropertySet > DocInfoProps(docinfo, UNO_QUERY );
        Any mTitle;
        mTitle = makeAny(OUString::createFromAscii("First attempt"));  //another method to create a PropertyValue with makeAny()
        Any *test_pointer = &mTitle; // testing
        DocInfoProps->setPropertyValue( OUString::createFromAscii("My new Title"), *test_pointer );
}


void PPTController::accessDoc()
{



	Reference< XDrawPagesSupplier > oDoc(xComponent, UNO_QUERY);

	Reference< XDrawPages > drawpages = oDoc->getDrawPages();
	Reference< ::com::sun::star::container::XIndexAccess > pagecount(drawpages, UNO_QUERY); // for index access and counting usage

	// insert a new drawpage -- identifier: newDrawPage
	Reference< XDrawPage > newDrawPage = drawpages->insertNewByIndex(1);
	Reference< ::com::sun::star::container::XNamed > namecontainer(newDrawPage, UNO_QUERY);

	// count pages and print them out to stdout
	sal_Int16 countresult = pagecount->getCount();
	printf("\nThere are %d pages in the Impress document\n\n", countresult);


	// Query the XModel Interface
		Reference< XModel > rmodel(oDoc, UNO_QUERY);
		Reference< XController > ctl = rmodel->getCurrentController();

	// Query the XDrawView interface
		Reference< XDrawView > rDrawView(ctl, UNO_QUERY);

	//Loop through all pages and give Pagenumber+Pagename to each of them
	for (int icounter = 0; icounter < pagecount->getCount(); icounter++)
	{
			Any mPage = pagecount->getByIndex(icounter);
			Reference< XDrawPage > drawpage(mPage, UNO_QUERY);
			Reference< ::com::sun::star::container::XNamed > names(drawpage, UNO_QUERY);
			OUString pagename = names->getName();
			OString sName = OUStringToOString( pagename , RTL_TEXTENCODING_ASCII_US );
			printf("\n Page Number %d has the name %s", icounter, sName.getStr());


			if(icounter == 2)rDrawView->setCurrentPage(drawpage);

	}



	// Playing around with the inserted page...
	//namecontainer->setName(OUString::createFromAscii("My second page"));



	//ChangeTitle(oDoc);




	/*//create xSheetDocument
	Reference<XSpreadsheetDocument> xSheetDocument_local (xComponent,UNO_QUERY);

	xSheetDocument  = xSheetDocument_local;

	//create an instance of XSpreadsheets, which is a worksheets collection
	Reference<XSpreadsheets> xSheets=xSheetDocument->getSheets();

	//create a class to interact with single worksheets;

	//the single worksheets are referenced by an XIndexAccess interface
	Reference<XIndexAccess> xIndex (xSheets,UNO_QUERY);

	//take the first worksheet (index=0)...
	Any any=xIndex->getByIndex(0);

	//finally, assign the first worksheet to xSheet
	any >>= xSheet;*/
}

void PPTController::modifyDoc()
{
	//create an XCellRange interface to interact with cells ranges
	Reference<XCellRange> xCellRange(xSheet,UNO_QUERY);

	//create an XCell interface to interact with single cells
	Reference<XCell> xCell;

	//take the cell located in column 5, row 6
	int column=5;
	int row=6;
	xCell=xCellRange->getCellByPosition(column,row);

	//write a number in the cell
	xCell->setValue(1960);

	//change cell
	column=6;
	row=5;
	xCell=xCellRange->getCellByPosition(column,row);

	//write a string in the cell
	OUString sString = OUString::createFromAscii("stringa");

	xCell->setFormula(sString);
}
void PPTController::printDoc()
{
	//open an XPrintable interface, linked to xSheetDocument
	Reference<XPrintable> xPrintable(xSheetDocument,UNO_QUERY);

	//load the printer setting
	Sequence<PropertyValue> pPrinter=xPrintable->getPrinter();

	//try to modify the PaperOrientation property
	OUString orient=OUString::createFromAscii("PaperOrientation");
	int k=0;
	//check the names until PaperOrientation
	do
	  {
	  if(orient.compareTo(pPrinter[k].Name)==0)
	    {
	    pPrinter[k].Value <<= PaperOrientation_LANDSCAPE;
	    }
	    k++;
	  }
	while(orient.compareTo(pPrinter[k].Name)!=0);


	//assign properties to the printer
	xPrintable->setPrinter(pPrinter);

	//print
	xPrintable->print(pPrinter);
}

void PPTController::disconnect()
{
	//try to close xComponent, until dispose() succeeds
	char b=0;
	while(b==0)
	  {
	  try
	    {
	    xComponent->dispose();
	    }
	  catch(...)
	    {
	     b=1;
	     }
	  }

	//delete the client-side service factory
	Reference<XComponent>
	::query(xMultiComponentFactoryClient)->dispose();
}
