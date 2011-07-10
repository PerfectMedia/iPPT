/*
 * PPTController.hpp
 *
 *  Created on: Jul 9, 2011
 *      Author: mordonez
 */

#ifndef PPTCONTROLLER_HPP_
#define PPTCONTROLLER_HPP_

#include <stdio.h>
#include <cppuhelper/bootstrap.hxx>
#include <osl/file.hxx>
#include <osl/process.h>
#include <iostream>

#include <com/sun/star/frame/XDesktop.hpp>
#include <com/sun/star/bridge/XUnoUrlResolver.hpp>
#include <com/sun/star/frame/XComponentLoader.hpp>
#include <com/sun/star/beans/XPropertySet.hpp>
#include <com/sun/star/sheet/XSpreadsheetDocument.hpp>

#include <com/sun/star/drawing/XDrawPagesSupplier.hpp>
#include <com/sun/star/drawing/XDrawPage.hpp>
#include <com/sun/star/drawing/XDrawPages.hpp>
#include <com/sun/star/drawing/XDrawView.hpp>
#include <com/sun/star/document/XDocumentInfoSupplier.hpp>
#include <com/sun/star/document/XDocumentInfo.hpp>
#include <com/sun/star/container/XNamed.hpp>

#include <com/sun/star/sheet/XSpreadsheets.hpp>
#include <com/sun/star/sheet/XSpreadsheet.hpp>
#include <com/sun/star/table/XCell.hpp>
#include <com/sun/star/table/XCellRange.hpp>
#include <com/sun/star/container/XIndexAccess.hpp>
#include <com/sun/star/view/XPrintable.hpp>
#include <com/sun/star/view/PaperOrientation.hpp>
#include <com/sun/star/registry/XSimpleRegistry.hpp>
#include <com/sun/star/lang/XMultiComponentFactory.hpp>
#include <com/sun/star/lang/IllegalArgumentException.hpp>
#include <string.h>
#include <unistd.h>

using namespace std;
using namespace rtl;
using namespace cppu;
using namespace com::sun::star::view;
using namespace com::sun::star::table;
using namespace com::sun::star::container;
using namespace com::sun::star::sheet;
using namespace com::sun::star::uno;
using namespace com::sun::star::lang;
using namespace com::sun::star::beans;
using namespace com::sun::star::bridge;
using namespace com::sun::star::frame;
using namespace com::sun::star::registry;

using namespace com::sun::star::drawing;

class PPTController
{
public:
	PPTController();
	void connect();
	void openDoc();
	void accessDoc();
	void modifyDoc();
	void printDoc();
	void disconnect();

private:
	string getCurrentDir();
};


#endif /* PPTCONTROLLER_HPP_ */
