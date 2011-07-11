/*
 * PPTController.cpp
 *
 *  Created on: Jul 9, 2011
 *      Author: mordonez
 */

#include "PPTController.hpp"



Reference<XInterface> xInterface;
Reference<XComponentContext> xComponentContext;
Reference<XComponent> xComponent;
Reference<XComponentLoader>xComponentLoader;
Reference<XMultiComponentFactory> xMultiComponentFactoryClient;
Reference< XDrawPages > drawpages;
Reference< XDrawView > drawview;
OUString sService;

int current_page = 0;

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


	string registry = getCurrentDir()+"/src/iPPT.rdb";


	// ... and connect it to the registry file: iPPT.rdb, current directory
	OUString sRdbFile=OUString::createFromAscii(registry.c_str());
	try
	{
		xSimpleRegistry->open(sRdbFile,sal_True,sal_False);
		cout << registry << endl;
	}
	catch (InvalidRegistryException e)
	{
		 OString o = OUStringToOString( e.Message, RTL_TEXTENCODING_ASCII_US );
		 printf( "An error occurred: %s\n", o.pData->buffer );
	}

	//open an  XComponentContext based on the registry file in
	// xSimpleRegistry
	try
	{
		xComponentContext = bootstrap_InitialComponentContext(xSimpleRegistry);
	}
	catch(Exception e)
	{
		cout << "error "<< endl;
		OString o = OUStringToOString( e.Message, RTL_TEXTENCODING_ASCII_US );
		printf( "An error occurred: %s\n", o.pData->buffer );
	}

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

void PPTController::accessDoc()
{



	Reference< XDrawPagesSupplier > oDoc(xComponent, UNO_QUERY);

	drawpages = oDoc->getDrawPages();
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
		drawview = rDrawView;

	//***************TEST PAGES*************/
	/*//Loop through all pages and give Pagenumber+Pagename to each of them
	for (int icounter = 0; icounter < pagecount->getCount(); icounter++)
	{
			Any mPage = pagecount->getByIndex(icounter);
			Reference< XDrawPage > drawpage(mPage, UNO_QUERY);
			Reference< ::com::sun::star::container::XNamed > names(drawpage, UNO_QUERY);
			OUString pagename = names->getName();
			OString sName = OUStringToOString( pagename , RTL_TEXTENCODING_ASCII_US );
			printf("\n Page Number %d has the name %s", icounter, sName.getStr());


			if(icounter == 2)rDrawView->setCurrentPage(drawpage);

	}*/
}

void PPTController::moveToNext()
{
	Reference< ::com::sun::star::container::XIndexAccess > pagecount(drawpages, UNO_QUERY);

	cout << "Pagina actual " << current_page << endl;

	if(current_page < pagecount->getCount())
	{
		current_page++;
		Any mPage = pagecount->getByIndex(current_page);
		Reference< XDrawPage > drawpage(mPage, UNO_QUERY);

		drawview->setCurrentPage(drawpage);
	}
}
void PPTController::moveToPrev()
{
	Reference< ::com::sun::star::container::XIndexAccess > pagecount(drawpages, UNO_QUERY);

	cout << "Pagina actual " << current_page << endl;

	if(current_page > 0)
	{
		current_page--;
		Any mPage = pagecount->getByIndex(current_page);
		Reference< XDrawPage > drawpage(mPage, UNO_QUERY);

		drawview->setCurrentPage(drawpage);
	}
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


int PPTController::currentPage()
{
	return current_page;
}
void PPTController::setCurrentPage(int page)
{
	current_page = page;
}
