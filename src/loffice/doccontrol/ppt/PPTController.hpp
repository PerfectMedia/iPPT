/*
 * PPTController.hpp
 *
 *  Created on: Jul 9, 2011
 *      Author: mordonez
 */

#ifndef PPTCONTROLLER_HPP_
#define PPTCONTROLLER_HPP_

#include <cppuhelper/bootstrap.hxx>
#include <osl/file.hxx>
#include <osl/process.h>

#include <com/sun/star/frame/XDesktop.hpp>
#include <com/sun/star/frame/XComponentLoader.hpp>

#include <com/sun/star/bridge/XUnoUrlResolver.hpp>

#include <com/sun/star/beans/XPropertySet.hpp>

#include <com/sun/star/drawing/XDrawPagesSupplier.hpp>
#include <com/sun/star/drawing/XDrawPage.hpp>
#include <com/sun/star/drawing/XDrawPages.hpp>
#include <com/sun/star/drawing/XDrawView.hpp>

#include <com/sun/star/document/XDocumentInfoSupplier.hpp>
#include <com/sun/star/document/XDocumentInfo.hpp>
#include <com/sun/star/container/XNamed.hpp>
#include <com/sun/star/container/XIndexAccess.hpp>

#include <com/sun/star/registry/XSimpleRegistry.hpp>

#include <com/sun/star/lang/XMultiComponentFactory.hpp>
#include <com/sun/star/lang/IllegalArgumentException.hpp>
#include <com/sun/star/uno/Exception.hpp>

#include <stdio.h>
#include <iostream>
#include <string.h>
#include <unistd.h>

using namespace std;
using namespace rtl;
using namespace cppu;
using namespace com::sun::star::container;
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
	void moveToNext();
	void moveToPrev();
	void disconnect();

	int currentPage();
	void setCurrentPage(int page);

private:


	string getCurrentDir();
};


#endif /* PPTCONTROLLER_HPP_ */
