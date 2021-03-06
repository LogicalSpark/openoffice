/**************************************************************
 * 
 * Licensed to the Apache Software Foundation (ASF) under one
 * or more contributor license agreements.  See the NOTICE file
 * distributed with this work for additional information
 * regarding copyright ownership.  The ASF licenses this file
 * to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance
 * with the License.  You may obtain a copy of the License at
 * 
 *   http://www.apache.org/licenses/LICENSE-2.0
 * 
 * Unless required by applicable law or agreed to in writing,
 * software distributed under the License is distributed on an
 * "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
 * KIND, either express or implied.  See the License for the
 * specific language governing permissions and limitations
 * under the License.
 * 
 *************************************************************/


// MARKER(update_precomp.py): autogen include statement, do not remove
#include "precompiled_svx.hxx"

#ifndef _COM_SUN_STAR_ACCESSIBILITY_ACCESSIBLEROLE_HPP_
#include <com/sun/star/accessibility/AccessibleRole.hpp>
#endif
#ifndef _COM_SUN_STAR_ACCESSIBILITY_ACCESSIBLEEVENTID_HPP_
#include <com/sun/star/accessibility/AccessibleEventId.hpp>
#endif
#ifndef _UTL_ACCESSIBLESTATESETHELPER_HXX_
#include <unotools/accessiblestatesethelper.hxx>
#endif
#ifndef _COM_SUN_STAR_ACCESSIBILITY_ACCESSIBLESTATETYPE_HPP_
#include <com/sun/star/accessibility/AccessibleStateType.hpp>
#endif

#ifndef	_COM_SUN_STAR_BEANS_PROPERTYCHANGEEVENT_HPP_
#include <com/sun/star/beans/PropertyChangeEvent.hpp>
#endif

#ifndef _COM_SUN_STAR_AWT_XWINDOW_HPP_
#include <com/sun/star/awt/XWindow.hpp>
#endif

#ifndef _CPPUHELPER_TYPEPROVIDER_HXX_
#include <cppuhelper/typeprovider.hxx>
#endif

#ifndef _TOOLKIT_HELPER_VCLUNOHELPER_HXX_
#include <toolkit/helper/vclunohelper.hxx>
#endif
#ifndef _TOOLKIT_HELPER_CONVERT_HXX_
#include <toolkit/helper/convert.hxx>
#endif

#ifndef _SV_SVAPP_HXX
#include <vcl/svapp.hxx>
#endif

#ifndef _OSL_MUTEX_HXX_
#include <osl/mutex.hxx>
#endif
#ifndef _RTL_UUID_H_
#include <rtl/uuid.h>
#endif
#ifndef _TOOLS_DEBUG_HXX
#include <tools/debug.hxx>
#endif
#ifndef _SV_GEN_HXX
#include <tools/gen.hxx>
#endif

#include <svx/dialogs.hrc>
#include "accessibility.hrc"
#include <svx/dlgctrl.hxx>

#ifndef _SVX_DIALMGR_HXX
#include <svx/dialmgr.hxx>
#endif
#ifndef COMPHELPER_ACCESSIBLE_EVENT_NOTIFIER
#include <comphelper/accessibleeventnotifier.hxx>
#endif

#include <unotools/accessiblerelationsethelper.hxx>

#ifndef _SVXPIXELACCESSIBLECONTEXT_HXX
#include "svxpixelctlaccessiblecontext.hxx"
#endif
#ifndef _COM_SUN_STAR_ACCESSIBILITY_ACCESSIBLERELATIONTYPE_HPP_
#include <com/sun/star/accessibility/AccessibleRelationType.hpp>
#endif
using namespace ::cppu;
using namespace ::osl;
using namespace	::rtl;
using namespace	::com::sun::star;
using namespace	::com::sun::star::uno;
using namespace	::com::sun::star::accessibility;

SvxPixelCtlAccessible::SvxPixelCtlAccessible( SvxPixelCtl& rControl) :
	SvxPixelCtlAccessible_BASE(m_aMutex),
    pPixelCtl(&rControl),
    mnClientId(0)
{
    //FreeResource();
}

SvxPixelCtlAccessible::~SvxPixelCtlAccessible()
{
//	DBG_DTOR( SvxPixelCtlAccessible, NULL );

	if( IsAlive() )
	{
		osl_incrementInterlockedCount( &m_refCount );
		dispose();		// set mpRepr = NULL & release all childs
	}
}
/*-- 04.02.2002 14:11:55---------------------------------------------------

  -----------------------------------------------------------------------*/
uno::Reference< XAccessibleContext > SvxPixelCtlAccessible::getAccessibleContext(  )
    throw (uno::RuntimeException)
{
    return this;
}

sal_Int32 SvxPixelCtlAccessible::getAccessibleChildCount(  ) throw (uno::RuntimeException)
{
    ::osl::MutexGuard	aGuard( m_aMutex );
    IsValid();
	if(pPixelCtl)
	{
	    return pPixelCtl->GetSquares();
	}
	else
		return 0;
}
/*-- 04.02.2002 14:11:56---------------------------------------------------

  -----------------------------------------------------------------------*/
uno::Reference< XAccessible > SvxPixelCtlAccessible::getAccessibleChild( sal_Int32 i )
    throw (uno::RuntimeException)
{
    ::osl::MutexGuard	aGuard( m_aMutex );
    IsValid();
    if ( i < 0 || i >= getAccessibleChildCount())
	throw lang::IndexOutOfBoundsException();
    uno::Reference <XAccessible> xAcc;
    if(pPixelCtl)
	{
		return CreateChild(i, pPixelCtl->IndexToPoint(i));
	}
    else
		return xAcc;
    /*
    throw lang::IndexOutOfBoundsException (
        ::rtl::OUString::createFromAscii ("no child with index " + i),
		NULL);
    */		
}



uno::Reference< XAccessible > SvxPixelCtlAccessible::getAccessibleParent(  )
    throw (uno::RuntimeException)
{
    ::osl::MutexGuard	aGuard( m_aMutex );
    IsValid();
    uno::Reference< XAccessible > xRet;
    if(pPixelCtl)
	    xRet = pPixelCtl->GetParent()->GetAccessible( sal_True );
    return xRet;
}

sal_Int32 SvxPixelCtlAccessible::getAccessibleIndexInParent(  )
    throw (uno::RuntimeException)
{
    ::osl::MutexGuard	aGuard( m_aMutex );
    IsValid();
    sal_uInt16 nIdx = 0;
    if(pPixelCtl)
    {
        Window* pTabPage = pPixelCtl->GetParent();
        sal_uInt16 nChildren = pTabPage->GetChildCount();
        for(nIdx = 0; nIdx < nChildren; nIdx++)
            if(pTabPage->GetChild( nIdx ) == pPixelCtl)
                break;
    }
    return nIdx;
}
/*-- 04.02.2002 14:11:57---------------------------------------------------

  -----------------------------------------------------------------------*/
sal_Int16 SvxPixelCtlAccessible::getAccessibleRole(  ) throw (uno::RuntimeException)
{
    return AccessibleRole::LIST;
}

::rtl::OUString SvxPixelCtlAccessible::getAccessibleDescription(  )
    throw (uno::RuntimeException)
{

    ::osl::MutexGuard	aGuard( m_aMutex );
    IsValid();
    if(pPixelCtl)
	return pPixelCtl->GetAccessibleDescription();
    else
	return String();

}

::rtl::OUString SvxPixelCtlAccessible::getAccessibleName(  )
    throw (uno::RuntimeException)
{
	
    ::osl::MutexGuard	aGuard( m_aMutex );
    IsValid();
    if(pPixelCtl)
	    return pPixelCtl->GetAccessibleName();
    else
	    return String();

}

uno::Reference< XAccessibleRelationSet > SvxPixelCtlAccessible::getAccessibleRelationSet(  )
    throw (uno::RuntimeException)
{
    ::osl::MutexGuard	aGuard( m_aMutex );
    IsValid();
	Window* pWindow = (Window*)pPixelCtl;
	utl::AccessibleRelationSetHelper* rRelationSet = new utl::AccessibleRelationSetHelper;
	uno::Reference< accessibility::XAccessibleRelationSet > rSet = rRelationSet;
	if ( pWindow )
	{
		Window *pLabeledBy = pWindow->GetAccessibleRelationLabeledBy();
		if ( pLabeledBy && pLabeledBy != pWindow )
		{
			uno::Sequence< uno::Reference< uno::XInterface > > aSequence(1);
			aSequence[0] = pLabeledBy->GetAccessible();
			rRelationSet->AddRelation( accessibility::AccessibleRelation( accessibility::AccessibleRelationType::LABELED_BY, aSequence ) );
		}

		Window* pMemberOf = pWindow->GetAccessibleRelationMemberOf();
		if ( pMemberOf && pMemberOf != pWindow )
		{
			uno::Sequence< uno::Reference< uno::XInterface > > aSequence(1);
			aSequence[0] = pMemberOf->GetAccessible();
			rRelationSet->AddRelation( accessibility::AccessibleRelation( accessibility::AccessibleRelationType::MEMBER_OF, aSequence ) );
		}
		return rSet;
	}
    
    return new utl::AccessibleRelationSetHelper;
}


uno::Reference< XAccessibleStateSet > SvxPixelCtlAccessible::getAccessibleStateSet(  )
    throw (uno::RuntimeException)
{
    ::osl::MutexGuard	aGuard( m_aMutex );
    utl::AccessibleStateSetHelper* pStateSetHelper = new utl::AccessibleStateSetHelper;
    uno::Reference< XAccessibleStateSet > xRet = pStateSetHelper;
	
    if(!pPixelCtl)
        pStateSetHelper->AddState(AccessibleStateType::DEFUNC);
    else
    {
        const sal_Int16 aStandardStates[] =
        {
            AccessibleStateType::FOCUSABLE,
				AccessibleStateType::SELECTABLE,
				AccessibleStateType::SHOWING,
				AccessibleStateType::VISIBLE,
				AccessibleStateType::OPAQUE,
				0};
			
			sal_Int16 nState = 0;
			while(aStandardStates[nState])
			{
				pStateSetHelper->AddState(aStandardStates[nState++]);
			}
			if(pPixelCtl->IsEnabled())
				pStateSetHelper->AddState(AccessibleStateType::ENABLED);
			if(pPixelCtl->HasFocus())
				pStateSetHelper->AddState(AccessibleStateType::FOCUSED);
			pStateSetHelper->AddState(AccessibleStateType::MANAGES_DESCENDANTS);	
    }
    return xRet;
}


com::sun::star::lang::Locale SvxPixelCtlAccessible::getLocale(  )
    throw (IllegalAccessibleComponentStateException, uno::RuntimeException)
{
	::osl::MutexGuard	aGuard( m_aMutex );
	if( getAccessibleParent().is() )
    {
    	uno::Reference< XAccessibleContext >		xParentContext( getAccessibleParent()->getAccessibleContext() );
        if( xParentContext.is() )
	    	return xParentContext->getLocale();
    }

    //	No locale and no parent.  Therefore throw exception to indicate this
    //	cluelessness.
    throw IllegalAccessibleComponentStateException();
}


sal_Bool SvxPixelCtlAccessible::containsPoint( const awt::Point& aPt )
    throw (uno::RuntimeException)
{
    ::osl::MutexGuard	aGuard( m_aMutex );
    IsValid();
    Point aPoint(aPt.X, aPt.Y);
    if(pPixelCtl)
	    return (aPoint.X() >= 0)
	        && (aPoint.X() < pPixelCtl->GetSizePixel().getWidth())
	        && (aPoint.Y() >= 0)
	        && (aPoint.Y() < pPixelCtl->GetSizePixel().getHeight());
    else
	    return sal_False;
}
uno::Reference<XAccessible > SAL_CALL SvxPixelCtlAccessible::getAccessibleAtPoint (
        const awt::Point& aPoint) 
    throw (uno::RuntimeException)
{
	::osl::MutexGuard	aGuard( m_aMutex );
	ensureIsAlive();
	uno::Reference <XAccessible> xAcc;

	Point childPoint;
	childPoint.X() = aPoint.X;
	childPoint.Y() = aPoint.Y;

    if(pPixelCtl)
   	{
		Point pt= pPixelCtl->PixelToLogic(childPoint);
		long nIndex = pPixelCtl->PointToIndex(pt);
	    return CreateChild(nIndex,pPixelCtl->IndexToPoint(nIndex));
    }
    else
	   return xAcc;

}

awt::Rectangle SvxPixelCtlAccessible::getBounds(  ) throw (uno::RuntimeException)
{
    ::osl::MutexGuard	aGuard( m_aMutex );
    IsValid();
    Size aSz;
    Point aPos(0,0);
    awt::Rectangle aRet;
	if(pPixelCtl)
	{
	    aSz = pPixelCtl->GetSizePixel();	
	    aPos = pPixelCtl->GetPosPixel();
	    aRet.X = aPos.X();
	    aRet.Y = aPos.Y();
	    aRet.Width = aSz.Width();
	    aRet.Height = aSz.Height();
	}
    return aRet;
}

awt::Point SvxPixelCtlAccessible::getLocation(  ) throw (uno::RuntimeException)
{
    ::osl::MutexGuard	aGuard( m_aMutex );
    IsValid();
    Point aPos;
    aPos = pPixelCtl->GetPosPixel();
    awt::Point aRet(aPos.X(), aPos.Y());
    return aRet;
}

awt::Point SvxPixelCtlAccessible::getLocationOnScreen(  ) throw (uno::RuntimeException)
{
    ::osl::MutexGuard	aGuard( m_aMutex );
    IsValid();
    Rectangle rect;
    rect = pPixelCtl->GetWindowExtentsRelative(NULL);
    awt::Point aRet(rect.Left(),rect.Top() );
    return aRet;
}

awt::Size SvxPixelCtlAccessible::getSize(  ) throw (uno::RuntimeException)
{
    ::osl::MutexGuard	aGuard( m_aMutex );
    IsValid();
    Size aSz;
    aSz = pPixelCtl->GetSizePixel();
    awt::Size aRet(aSz.Width(),aSz.Height());
    return aRet;
}
void SvxPixelCtlAccessible::grabFocus(  ) throw (uno::RuntimeException)
{
    ::osl::MutexGuard	aGuard( m_aMutex );
    IsValid();
    if(pPixelCtl)
	pPixelCtl->GrabFocus();
}

sal_Int32 SvxPixelCtlAccessible::getForeground(  )
        throw (::com::sun::star::uno::RuntimeException)
{
    uno::Any aRet;
    ::osl::MutexGuard	aGuard( m_aMutex );
    IsValid();
    return pPixelCtl->GetControlForeground().GetColor();
}

sal_Int32 SvxPixelCtlAccessible::getBackground(  )
        throw (::com::sun::star::uno::RuntimeException)
{
    uno::Any aRet;
    ::osl::MutexGuard	aGuard( m_aMutex );
    IsValid();
    return pPixelCtl->GetControlBackground().GetColor();
}

::rtl::OUString SvxPixelCtlAccessible::getImplementationName(  ) throw (uno::RuntimeException)
{
    return rtl::OUString::createFromAscii("SvxPixelCtlAccessible");
}
/*-- 04.02.2002 14:12:05---------------------------------------------------

  -----------------------------------------------------------------------*/
const sal_Char sAccessible[]          = "Accessible";
const sal_Char sAccessibleContext[]   = "AccessibleContext";
const sal_Char sAccessibleComponent[] = "AccessibleComponent";
//const sal_Char sAccessibleTable[] = "AccessibleTable";

sal_Bool SvxPixelCtlAccessible::supportsService( const ::rtl::OUString& rServiceName )
    throw (uno::RuntimeException)
{
    return  rServiceName.equalsAsciiL( sAccessible         , sizeof(sAccessible         )-1 ) ||
            rServiceName.equalsAsciiL( sAccessibleContext  , sizeof(sAccessibleContext  )-1 ) ||
            rServiceName.equalsAsciiL( sAccessibleComponent, sizeof(sAccessibleComponent)-1 );// ||
//            rServiceName.equalsAsciiL( sAccessibleTable, sizeof(sAccessibleTable)-1 );
}
/*-- 04.02.2002 14:12:05---------------------------------------------------

  -----------------------------------------------------------------------*/
uno::Sequence< ::rtl::OUString > SvxPixelCtlAccessible::getSupportedServiceNames(  )
    throw (uno::RuntimeException)
{
    uno::Sequence< OUString > aRet(2);
	OUString* pArray = aRet.getArray();
    pArray[0] = OUString( RTL_CONSTASCII_USTRINGPARAM(sAccessible         ) );
    pArray[1] = OUString( RTL_CONSTASCII_USTRINGPARAM(sAccessibleContext  ) );
    pArray[2] = OUString( RTL_CONSTASCII_USTRINGPARAM(sAccessibleComponent) );
//    pArray[3] = OUString( RTL_CONSTASCII_USTRINGPARAM(sAccessibleTable) );
    return aRet;
}

// -----------------------------------------------------------------------------
// XAccessibleSelection
// -----------------------------------------------------------------------------
void SAL_CALL SvxPixelCtlAccessible::selectAccessibleChild( sal_Int32 nChildIndex ) throw (lang::IndexOutOfBoundsException, RuntimeException)
{
    ::osl::MutexGuard	aGuard( m_aMutex );
    IsValid();
	
	if ( nChildIndex < 0 || nChildIndex >= getAccessibleChildCount())
		throw lang::IndexOutOfBoundsException();

	long nIndex = pPixelCtl->ShowPosition(pPixelCtl->IndexToPoint(nChildIndex));
	NotifyChild(nIndex,sal_True,sal_False);
}
// -----------------------------------------------------------------------------
sal_Bool SAL_CALL SvxPixelCtlAccessible::isAccessibleChildSelected( sal_Int32 nChildIndex ) throw (lang::IndexOutOfBoundsException, RuntimeException)
{
    ::osl::MutexGuard	aGuard( m_aMutex );
	
    IsValid();

	return pPixelCtl->GetFoucsPosIndex() == nChildIndex;
}
// -----------------------------------------------------------------------------
void SAL_CALL SvxPixelCtlAccessible::clearAccessibleSelection(  ) throw (RuntimeException)
{
    ::osl::MutexGuard	aGuard( m_aMutex );
	
    IsValid();
	
}
// -----------------------------------------------------------------------------
void SAL_CALL SvxPixelCtlAccessible::selectAllAccessibleChildren(  ) throw (RuntimeException)
{
    ::osl::MutexGuard	aGuard( m_aMutex );
	
    IsValid();
	
}
// -----------------------------------------------------------------------------
sal_Int32 SAL_CALL SvxPixelCtlAccessible::getSelectedAccessibleChildCount(  ) throw (RuntimeException)
{
    ::osl::MutexGuard	aGuard( m_aMutex );
	
    IsValid();
	
	return 1;
}
// -----------------------------------------------------------------------------
uno::Reference< XAccessible > SAL_CALL SvxPixelCtlAccessible::getSelectedAccessibleChild( sal_Int32 nSelectedChildIndex ) throw (lang::IndexOutOfBoundsException, RuntimeException)
{
    ::osl::MutexGuard	aGuard( m_aMutex );
	
    IsValid();
	
	if ( nSelectedChildIndex >= 1)
		throw lang::IndexOutOfBoundsException();
	
	uno::Reference< XAccessible > xChild;
	if(pPixelCtl)
	{
		if(m_xCurChild.is())
		{
			xChild = m_xCurChild;
		}
	}
	return xChild;
}
// -----------------------------------------------------------------------------
void SAL_CALL SvxPixelCtlAccessible::deselectAccessibleChild( sal_Int32 ) throw (lang::IndexOutOfBoundsException, RuntimeException)
{
    ::osl::MutexGuard	aGuard( m_aMutex );
	
    IsValid();
	
	
}

// Added by lq
void SvxPixelCtlAccessible::ensureIsAlive() const
    throw ( lang::DisposedException )
{
    if( !IsAlive() )
        throw lang::DisposedException();
}

void SvxPixelCtlAccessible::ensureIsValidRow( sal_Int32 nRow )
    throw ( lang::IndexOutOfBoundsException )
{
    if( nRow >= pPixelCtl->GetHeight() || nRow <0)
        throw lang::IndexOutOfBoundsException(
            OUString( RTL_CONSTASCII_USTRINGPARAM( "row index is invalid" ) ), *this );
}

void SvxPixelCtlAccessible::ensureIsValidColumn( sal_Int32 nColumn )
    throw ( lang::IndexOutOfBoundsException )
{
    if( nColumn >= pPixelCtl->GetWidth() || nColumn <0 )
        throw lang::IndexOutOfBoundsException(
            OUString( RTL_CONSTASCII_USTRINGPARAM("column index is invalid") ), *this );
}

void SvxPixelCtlAccessible::ensureIsValidAddress(
        sal_Int32 nRow, sal_Int32 nColumn )
    throw ( lang::IndexOutOfBoundsException )
{
    ensureIsValidRow( nRow );
    ensureIsValidColumn( nColumn );
}

void SvxPixelCtlAccessible::ensureIsValidIndex( sal_Int32 nChildIndex )
    throw ( lang::IndexOutOfBoundsException )
{
    if( nChildIndex >=  pPixelCtl->GetSquares())
        throw lang::IndexOutOfBoundsException(
            OUString( RTL_CONSTASCII_USTRINGPARAM("child index is invalid") ), *this );
}

// XAccessibleTable -----------------------------------------------------------
/*
sal_Int32 SAL_CALL SvxPixelCtlAccessible::getAccessibleRowCount()
    throw ( uno::RuntimeException )
{
   ::osl::MutexGuard	aGuard( m_aMutex );
   ensureIsAlive();
    return pPixelCtl->GetLineCount();
}

sal_Int32 SAL_CALL SvxPixelCtlAccessible::getAccessibleColumnCount()
    throw ( uno::RuntimeException )
{
    ::osl::MutexGuard	aGuard( m_aMutex );
    ensureIsAlive();
    return pPixelCtl->GetLineCount();
}

sal_Int32 SAL_CALL SvxPixelCtlAccessible::getAccessibleRowExtentAt(
        sal_Int32 nRow, sal_Int32 nColumn )
    throw ( lang::IndexOutOfBoundsException, uno::RuntimeException )
{
    ::osl::MutexGuard	aGuard( m_aMutex );
    ensureIsAlive();
    return 1;   // merged cells not supported
}

sal_Int32 SAL_CALL SvxPixelCtlAccessible::getAccessibleColumnExtentAt(
        sal_Int32 nRow, sal_Int32 nColumn )
    throw ( lang::IndexOutOfBoundsException, uno::RuntimeException )
{
    ::osl::MutexGuard	aGuard( m_aMutex );
    ensureIsAlive();
    return 1;   // merged cells not supported
}

uno::Reference< XAccessible > SAL_CALL SvxPixelCtlAccessible::getAccessibleCaption()
    throw ( uno::RuntimeException )
{
	uno::Reference< XAccessible > xAccessble;
    ensureIsAlive();
    return xAccessble;    // not supported
}

uno::Reference< XAccessible > SAL_CALL SvxPixelCtlAccessible::getAccessibleSummary()
    throw ( uno::RuntimeException )
{
	uno::Reference< XAccessible > xAccessble;
    ensureIsAlive();
    return xAccessble;    // not supported
}

sal_Int32 SAL_CALL SvxPixelCtlAccessible::getAccessibleIndex(
        sal_Int32 nRow, sal_Int32 nColumn )
    throw ( lang::IndexOutOfBoundsException, uno::RuntimeException )
{
    ::osl::MutexGuard	aGuard( m_aMutex );
    ensureIsAlive();
    ensureIsValidAddress(nRow,nColumn);
    return nRow + nColumn * pPixelCtl->GetLineCount() ;
}

sal_Int32 SAL_CALL SvxPixelCtlAccessible::getAccessibleRow( sal_Int32 nChildIndex )
    throw ( lang::IndexOutOfBoundsException, uno::RuntimeException )
{
    ::osl::MutexGuard	aGuard( m_aMutex );
    ensureIsAlive();
    ensureIsValidIndex( nChildIndex );
    return nChildIndex/pPixelCtl->GetLineCount();
}

sal_Int32 SAL_CALL SvxPixelCtlAccessible::getAccessibleColumn( sal_Int32 nChildIndex )
    throw ( lang::IndexOutOfBoundsException, uno::RuntimeException )
{
    ::osl::MutexGuard	aGuard( m_aMutex );
    ensureIsAlive();
    ensureIsValidIndex( nChildIndex );
    return nChildIndex%pPixelCtl->GetLineCount();
}

::rtl::OUString SAL_CALL SvxPixelCtlAccessible::getAccessibleRowDescription( sal_Int32 nRow )
    throw ( lang::IndexOutOfBoundsException, uno::RuntimeException )
{
    ::osl::MutexGuard	aGuard( m_aMutex );
    ensureIsAlive();
    ensureIsValidRow( nRow );
    return ::rtl::OUString::createFromAscii ("");
}

::rtl::OUString SAL_CALL SvxPixelCtlAccessible::getAccessibleColumnDescription( sal_Int32 nColumn )
    throw ( lang::IndexOutOfBoundsException, uno::RuntimeException )
{
    ::osl::MutexGuard	aGuard( m_aMutex );
    ensureIsAlive();
    ensureIsValidColumn( nColumn );
    return ::rtl::OUString::createFromAscii ("");
}

uno::Reference< XAccessibleTable > SAL_CALL SvxPixelCtlAccessible::getAccessibleRowHeaders()
    throw ( uno::RuntimeException )
{
    ::osl::MutexGuard	aGuard( m_aMutex );
    uno::Reference< XAccessibleTable > xAccessble;
    ensureIsAlive();
    return xAccessble;
}

uno::Reference< XAccessibleTable > SAL_CALL SvxPixelCtlAccessible::getAccessibleColumnHeaders()
    throw ( uno::RuntimeException )
{
    ::osl::MutexGuard	aGuard( m_aMutex );
    uno::Reference< XAccessibleTable > xAccessble;
    ensureIsAlive();
    return xAccessble;
}

Sequence< sal_Int32 > SAL_CALL SvxPixelCtlAccessible::getSelectedAccessibleRows()
    throw ( uno::RuntimeException )
{
    ::osl::MutexGuard	aGuard( m_aMutex );
    Sequence< sal_Int32 > accRows;
    ensureIsAlive();

    return accRows;
}

Sequence< sal_Int32 > SAL_CALL SvxPixelCtlAccessible::getSelectedAccessibleColumns()
    throw ( uno::RuntimeException )
{
    ::osl::MutexGuard	aGuard( m_aMutex );
    Sequence< sal_Int32 > accColumns;
    ensureIsAlive();

    return accColumns;
}

sal_Bool SAL_CALL SvxPixelCtlAccessible::isAccessibleRowSelected( sal_Int32 nRow )
    throw ( lang::IndexOutOfBoundsException, uno::RuntimeException )
{
    ::osl::MutexGuard	aGuard( m_aMutex );
    ensureIsAlive();
    ensureIsValidRow( nRow );
    return sal_False;
}

sal_Bool SAL_CALL SvxPixelCtlAccessible::isAccessibleColumnSelected( sal_Int32 nColumn )
    throw ( lang::IndexOutOfBoundsException, uno::RuntimeException )
{
    ::osl::MutexGuard	aGuard( m_aMutex );
    ensureIsAlive();
    ensureIsValidColumn( nColumn );
    return sal_False;
}

uno::Reference< XAccessible > SAL_CALL SvxPixelCtlAccessible::getAccessibleCellAt(
        sal_Int32 nRow, sal_Int32 nColumn )
    throw ( lang::IndexOutOfBoundsException, uno::RuntimeException )
{
    ::osl::MutexGuard	aGuard( m_aMutex );
    ensureIsAlive();
    ensureIsValidAddress( nRow, nColumn );
    return getAccessibleChild(nRow*pPixelCtl->GetLineCount()+nColumn);
}

sal_Bool SAL_CALL SvxPixelCtlAccessible::isAccessibleSelected(
        sal_Int32 nRow, sal_Int32 nColumn )
    throw ( lang::IndexOutOfBoundsException, uno::RuntimeException )
{
    ::osl::MutexGuard	aGuard( m_aMutex );
    ensureIsAlive();
    ensureIsValidAddress( nRow, nColumn );
    return isAccessibleChildSelected(nRow*pPixelCtl->GetLineCount()+nColumn);
}
// Added by lq end
*/

//XAccessibleEventBroadcaster
void SAL_CALL SvxPixelCtlAccessible::addEventListener( const uno::Reference< XAccessibleEventListener >& xListener )  throw( RuntimeException )
{
	if (xListener.is())
    {
		::osl::MutexGuard	aGuard( m_aMutex );
		if (!mnClientId)
	            mnClientId = comphelper::AccessibleEventNotifier::registerClient( );
		comphelper::AccessibleEventNotifier::addEventListener( mnClientId, xListener );
    }
}

void SAL_CALL SvxPixelCtlAccessible::removeEventListener( const uno::Reference< XAccessibleEventListener >& xListener )
    throw( RuntimeException )
{
	if (xListener.is())
	{
    	::osl::MutexGuard	aGuard( m_aMutex );

        sal_Int32 nListenerCount = comphelper::AccessibleEventNotifier::removeEventListener( mnClientId, xListener );
		if ( !nListenerCount )
		{
			comphelper::AccessibleEventNotifier::revokeClient( mnClientId );
			mnClientId = 0;
		}
	}
}
void SvxPixelCtlAccessible::CommitChange( const AccessibleEventObject& rEvent )
{
	if (mnClientId)
		comphelper::AccessibleEventNotifier::addEvent( mnClientId, rEvent );
}

//Solution:Add the event handling method
void SvxPixelCtlAccessible::FireAccessibleEvent (short nEventId, const ::com::sun::star::uno::Any& rOld, const ::com::sun::star::uno::Any& rNew)
{
	const uno::Reference< XInterface >	xSource( *this );
	CommitChange( AccessibleEventObject( xSource, nEventId, rNew,rOld ) );
}

void SAL_CALL SvxPixelCtlAccessible::disposing()
{
	if( !rBHelper.bDisposed )
	{
		{
			::osl::MutexGuard	aGuard( m_aMutex );
			if ( mnClientId )
			{
				comphelper::AccessibleEventNotifier::revokeClientNotifyDisposing( mnClientId, *this );
				mnClientId =  0;
			}
		}
	    //mxParent = uno::Reference< XAccessible >();
	    
	}
}
void SvxPixelCtlAccessible::Invalidate()
{
	pPixelCtl = 0;
}
void SvxPixelCtlAccessible::ThrowExceptionIfNotAlive( void ) throw( lang::DisposedException )
{
	if( IsNotAlive() )
		throw lang::DisposedException();
}
void SvxPixelCtlAccessible::IsValid() throw (uno::RuntimeException)
{
    if(!pPixelCtl)
        throw uno::RuntimeException();
}


void SvxPixelCtlAccessible::NotifyChild(long nIndex,sal_Bool bSelect ,sal_Bool bCheck)
{
	DBG_ASSERT( !(!bSelect && !bCheck),"" );//non is false

	SvxPixelCtlAccessibleChild *pChild= NULL;
	
	if (m_xCurChild.is())
	{
		pChild= static_cast<SvxPixelCtlAccessibleChild*>(m_xCurChild.get());
		DBG_ASSERT(pChild,"Child Must be Valid");
		if (pChild->getAccessibleIndexInParent() == nIndex )
		{
			if (bSelect)
			{
				pChild->SelectChild(sal_True);
			}
			if (bCheck)
			{
				pChild->ChangePixelColorOrBG(sal_Bool(pPixelCtl->GetBitmapPixel(sal_uInt16(nIndex))));
				pChild->CheckChild();
			}
			return ;
		}
	}
	uno::Reference <XAccessible> xNewChild =CreateChild(nIndex, pPixelCtl->IndexToPoint(nIndex));
	SvxPixelCtlAccessibleChild *pNewChild= static_cast<SvxPixelCtlAccessibleChild*>(xNewChild.get());
	DBG_ASSERT(pNewChild,"Child Must be Valid");

	Any aNewValue,aOldValue;
	aNewValue<<= xNewChild;
	FireAccessibleEvent(	AccessibleEventId::ACTIVE_DESCENDANT_CHANGED,
							aOldValue,
							aNewValue );

	if (bSelect)
	{
		if (pChild)
		{
			pChild->SelectChild(sal_False);
		}
		pNewChild->SelectChild(sal_True);
	}
	if (bCheck)
	{
		pNewChild->CheckChild();
	}
	m_xCurChild= xNewChild;


}

uno::Reference<XAccessible> SvxPixelCtlAccessible::CreateChild (long nIndex,Point mPoint)
{
	long nX = mPoint.X();
	long nY = mPoint.Y();
	if( Application::GetSettings().GetLayoutRTL())
	{
	    nX = (sal_uInt16) pPixelCtl->GetWidth() - 1 - nX;
	}

	sal_Bool bPixelColorOrBG= sal_Bool(pPixelCtl->GetBitmapPixel(sal_uInt16(nIndex)));
	Size size(pPixelCtl->GetWidth() / pPixelCtl->GetLineCount(),pPixelCtl->GetHeight() / pPixelCtl->GetLineCount());
	uno::Reference<XAccessible> xChild;
	xChild = new SvxPixelCtlAccessibleChild(pPixelCtl, 
				bPixelColorOrBG, 
				Point(nX,nY),
				Rectangle(mPoint,size),
				this,
				nIndex);

	return xChild;
}


void SvxPixelCtlAccessible::LoseFocus()
{
	m_xCurChild = uno::Reference< XAccessible >() ;
}

void SvxPixelCtlAccessibleChild::CheckChild()
{
	Any aChecked;
	aChecked <<= AccessibleStateType::CHECKED;

	if (m_bPixelColorOrBG)//Current Child State
	{
		FireAccessibleEvent(	AccessibleEventId::STATE_CHANGED,								
								Any(),
								aChecked);
	}
	else
	{
		FireAccessibleEvent(	AccessibleEventId::STATE_CHANGED,
								aChecked,
								Any() );
	}
}

void SvxPixelCtlAccessibleChild::SelectChild( sal_Bool bSelect)
{
	Any aSelected;
	aSelected <<= AccessibleStateType::SELECTED;

	if (bSelect)
	{
		FireAccessibleEvent(	AccessibleEventId::STATE_CHANGED,
								Any(),
								aSelected);
	}
	else
	{
		FireAccessibleEvent(	AccessibleEventId::STATE_CHANGED,
								aSelected,
								Any());
	}
}
void SvxPixelCtlAccessibleChild::FireAccessibleEvent (
	short nEventId, 
	const ::com::sun::star::uno::Any& rOld, 
	const ::com::sun::star::uno::Any& rNew)
{
	const uno::Reference< XInterface >	xSource( *this );
	CommitChange( AccessibleEventObject( xSource, nEventId, rNew,rOld ) );
}



DBG_NAME( SvxPixelCtlAccessibleChild )


SvxPixelCtlAccessibleChild::SvxPixelCtlAccessibleChild(
	SvxPixelCtl* rWindow, 
	sal_Bool bPixelColorOrBG,
	const Point &aPoint,
	const Rectangle& rBoundingBox,
	const uno::Reference<XAccessible>&	rxParent,
	long nIndexInParent ) :
	SvxPixelCtlAccessibleChild_BASE( m_aMutex ),
	mrParentWindow( rWindow ),
	mxParent(rxParent),
	m_bPixelColorOrBG(bPixelColorOrBG),
	maPoint(aPoint),
	mpBoundingBox( new Rectangle( rBoundingBox ) ),
	mnIndexInParent( nIndexInParent ),
	mnClientId( 0 )
{
	DBG_CTOR( SvxPixelCtlAccessibleChild, NULL );
}


SvxPixelCtlAccessibleChild::~SvxPixelCtlAccessibleChild()
{
	DBG_DTOR( SvxPixelCtlAccessibleChild, NULL );

	if( IsAlive() )
	{
		osl_incrementInterlockedCount( &m_refCount );
		dispose();		// set mpRepr = NULL & release all childs
	}
}

//=====  XAccessible  =========================================================

uno::Reference< XAccessibleContext> SAL_CALL SvxPixelCtlAccessibleChild::getAccessibleContext( void ) throw( RuntimeException )
{
	return this;
}

//=====  XAccessibleComponent  ================================================

sal_Bool SAL_CALL SvxPixelCtlAccessibleChild::containsPoint( const awt::Point& rPoint ) throw( RuntimeException )
{
	// no guard -> done in getBounds()
//	return GetBoundingBox().IsInside( VCLPoint( rPoint ) );
	return Rectangle( Point( 0, 0 ), GetBoundingBox().GetSize() ).IsInside( VCLPoint( rPoint ) );
}

uno::Reference< XAccessible > SAL_CALL SvxPixelCtlAccessibleChild::getAccessibleAtPoint( const awt::Point& ) throw( RuntimeException )
{
	return uno::Reference< XAccessible >();
}

awt::Rectangle SAL_CALL SvxPixelCtlAccessibleChild::getBounds() throw( RuntimeException )
{
	// no guard -> done in getBoundingBox()
	//Modified by lq, 09/26
	//return AWTRectangle( GetBoundingBox() );
	awt::Rectangle rect = AWTRectangle( GetBoundingBox() );
	rect.X = rect.X + mrParentWindow->GetClientWindowExtentsRelative(NULL).Left()-mrParentWindow->GetWindowExtentsRelative(NULL).Left();
	rect.Y = rect.Y + mrParentWindow->GetClientWindowExtentsRelative(NULL).Top()-mrParentWindow->GetWindowExtentsRelative(NULL).Top();
	return rect;
	// End
}

awt::Point SAL_CALL SvxPixelCtlAccessibleChild::getLocation() throw( RuntimeException )
{
	// no guard -> done in getBoundingBox()
	return AWTPoint( GetBoundingBox().TopLeft() );
}

awt::Point SAL_CALL SvxPixelCtlAccessibleChild::getLocationOnScreen() throw( RuntimeException )
{
	// no guard -> done in getBoundingBoxOnScreen()
	return AWTPoint( GetBoundingBoxOnScreen().TopLeft() );
}

awt::Size SAL_CALL SvxPixelCtlAccessibleChild::getSize() throw( RuntimeException )
{
	// no guard -> done in getBoundingBox()
	return AWTSize( GetBoundingBox().GetSize() );
}

void SAL_CALL SvxPixelCtlAccessibleChild::grabFocus() throw( RuntimeException )
{
}

sal_Int32 SvxPixelCtlAccessibleChild::getForeground(  ) 
        throw (::com::sun::star::uno::RuntimeException)
{
    //::vos::OGuard       aSolarGuard( Application::GetSolarMutex() );
    ::osl::MutexGuard   aGuard( m_aMutex );
    ThrowExceptionIfNotAlive();
    return mrParentWindow->GetControlForeground().GetColor();
}
sal_Int32 SvxPixelCtlAccessibleChild::getBackground(  ) 
        throw (::com::sun::star::uno::RuntimeException)
{
    //::vos::OGuard       aSolarGuard( Application::GetSolarMutex() );
    ::osl::MutexGuard   aGuard( m_aMutex );

    ThrowExceptionIfNotAlive();
    return mrParentWindow->GetControlBackground().GetColor();
}

//=====  XAccessibleContext  ==================================================

sal_Int32 SAL_CALL SvxPixelCtlAccessibleChild::getAccessibleChildCount( void ) throw( RuntimeException )
{
	return 0;
}

uno::Reference< XAccessible > SAL_CALL SvxPixelCtlAccessibleChild::getAccessibleChild( sal_Int32 ) throw ( RuntimeException )
{
	throw lang::IndexOutOfBoundsException();
}

uno::Reference< XAccessible > SAL_CALL SvxPixelCtlAccessibleChild::getAccessibleParent( void ) throw( RuntimeException )
{
	return mxParent;
}

sal_Int32 SAL_CALL SvxPixelCtlAccessibleChild::getAccessibleIndexInParent( void ) throw( RuntimeException )
{
   return mnIndexInParent;
}

sal_Int16 SAL_CALL SvxPixelCtlAccessibleChild::getAccessibleRole( void ) throw( RuntimeException )
{
	return AccessibleRole::CHECK_BOX;
}

OUString SAL_CALL SvxPixelCtlAccessibleChild::getAccessibleDescription( void ) throw( RuntimeException )
{
	::osl::MutexGuard	aGuard( m_aMutex );

	return  GetName();
}

OUString SAL_CALL SvxPixelCtlAccessibleChild::getAccessibleName( void ) throw( RuntimeException )
{
	::osl::MutexGuard	aGuard( m_aMutex );	
	return  GetName();
}

/**	Return empty uno::Reference to indicate that the relation set is not
	supported.
*/
uno::Reference<XAccessibleRelationSet> SAL_CALL SvxPixelCtlAccessibleChild::getAccessibleRelationSet( void ) throw( RuntimeException )
{
	return uno::Reference< XAccessibleRelationSet >();
}

uno::Reference< XAccessibleStateSet > SAL_CALL SvxPixelCtlAccessibleChild::getAccessibleStateSet( void ) throw( RuntimeException )
{
	::osl::MutexGuard						aGuard( m_aMutex );
	utl::AccessibleStateSetHelper*			pStateSetHelper = new utl::AccessibleStateSetHelper;

	if( IsAlive() )
	{

		pStateSetHelper->AddState( AccessibleStateType::TRANSIENT );
		pStateSetHelper->AddState( AccessibleStateType::ENABLED );
		pStateSetHelper->AddState( AccessibleStateType::OPAQUE );
		pStateSetHelper->AddState( AccessibleStateType::SELECTABLE );
		pStateSetHelper->AddState( AccessibleStateType::SHOWING );
		pStateSetHelper->AddState( AccessibleStateType::VISIBLE );

		if (mrParentWindow )
		{
			long nIndex = mrParentWindow->GetFoucsPosIndex();
			if ( nIndex == mnIndexInParent)
			{
				pStateSetHelper->AddState( AccessibleStateType::SELECTED );
			}
			if (mrParentWindow->GetBitmapPixel(sal_uInt16(mnIndexInParent)))
			{
				pStateSetHelper->AddState( AccessibleStateType::CHECKED );
			}
		}
	}
	else
		pStateSetHelper->AddState( AccessibleStateType::DEFUNC );

	return pStateSetHelper;
}

lang::Locale SAL_CALL SvxPixelCtlAccessibleChild::getLocale( void ) throw( IllegalAccessibleComponentStateException, RuntimeException )
{
	::osl::MutexGuard						aGuard( m_aMutex );
	if( mxParent.is() )
    {
    	uno::Reference< XAccessibleContext >		xParentContext( mxParent->getAccessibleContext() );
        if( xParentContext.is() )
	    	return xParentContext->getLocale();
    }

    //	No locale and no parent.  Therefore throw exception to indicate this
    //	cluelessness.
    throw IllegalAccessibleComponentStateException();
}

void SAL_CALL SvxPixelCtlAccessibleChild::addEventListener( const uno::Reference< XAccessibleEventListener >& xListener )
    throw( RuntimeException )
{
	if (xListener.is())
    {
    	::osl::MutexGuard	aGuard( m_aMutex );
		if (!mnClientId)
            mnClientId = comphelper::AccessibleEventNotifier::registerClient( );
		comphelper::AccessibleEventNotifier::addEventListener( mnClientId, xListener );
    }
}




void SAL_CALL SvxPixelCtlAccessibleChild::removeEventListener( const uno::Reference< XAccessibleEventListener >& xListener )
    throw( RuntimeException )
{
	if (xListener.is())
	{
    	::osl::MutexGuard	aGuard( m_aMutex );

        sal_Int32 nListenerCount = comphelper::AccessibleEventNotifier::removeEventListener( mnClientId, xListener );
		if ( !nListenerCount )
		{
			// no listeners anymore
			// -> revoke ourself. This may lead to the notifier thread dying (if we were the last client),
			// and at least to us not firing any events anymore, in case somebody calls
			// NotifyAccessibleEvent, again
			comphelper::AccessibleEventNotifier::revokeClient( mnClientId );
			mnClientId = 0;
		}
	}
}


//=====  XServiceInfo  ========================================================

OUString SAL_CALL SvxPixelCtlAccessibleChild::getImplementationName( void ) throw( RuntimeException )
{
	return OUString( RTL_CONSTASCII_USTRINGPARAM( "SvxPixelCtlAccessibleChild" ) );
}

sal_Bool SAL_CALL SvxPixelCtlAccessibleChild::supportsService( const OUString& rServiceName ) throw( RuntimeException )
{
    return  rServiceName.equalsAsciiL( sAccessible         , sizeof(sAccessible         )-1 ) ||
            rServiceName.equalsAsciiL( sAccessibleContext  , sizeof(sAccessibleContext  )-1 ) ||
            rServiceName.equalsAsciiL( sAccessibleComponent, sizeof(sAccessibleComponent)-1 );

}

Sequence< OUString > SAL_CALL SvxPixelCtlAccessibleChild::getSupportedServiceNames( void ) throw( RuntimeException )
{
    uno::Sequence< OUString > aRet(3);
	OUString* pArray = aRet.getArray();
    pArray[0] = OUString( RTL_CONSTASCII_USTRINGPARAM(sAccessible         ) );
    pArray[1] = OUString( RTL_CONSTASCII_USTRINGPARAM(sAccessibleContext  ) );
    pArray[2] = OUString( RTL_CONSTASCII_USTRINGPARAM(sAccessibleComponent) );
    return aRet;
}

//=====  internal  ============================================================

void SvxPixelCtlAccessibleChild::CommitChange( const AccessibleEventObject& rEvent )
{
	if (mnClientId)
		comphelper::AccessibleEventNotifier::addEvent( mnClientId, rEvent );
}

void SAL_CALL SvxPixelCtlAccessibleChild::disposing()
{
	if( !rBHelper.bDisposed )
	{
		::osl::MutexGuard	aGuard( m_aMutex );

        // Send a disposing to all listeners.
	    if ( mnClientId )
	    {
            comphelper::AccessibleEventNotifier::revokeClientNotifyDisposing( mnClientId, *this );
		    mnClientId =  0;
	    }

		mxParent = uno::Reference< XAccessible >();
        
	    delete mpBoundingBox;
	}
}

void SvxPixelCtlAccessibleChild::ThrowExceptionIfNotAlive( void ) throw( lang::DisposedException )
{
	if( IsNotAlive() )
		throw lang::DisposedException();
}

Rectangle SvxPixelCtlAccessibleChild::GetBoundingBoxOnScreen( void ) throw( RuntimeException )
{
	::osl::MutexGuard	aGuard( m_aMutex );

	// no ThrowExceptionIfNotAlive() because its done in GetBoundingBox()
	Rectangle			aRect( GetBoundingBox() );

	return Rectangle( mrParentWindow->OutputToAbsoluteScreenPixel( aRect.TopLeft() ), aRect.GetSize() );
}

Rectangle SvxPixelCtlAccessibleChild::GetBoundingBox( void ) throw( RuntimeException )
{
	// no guard necessary, because no one changes mpBoundingBox after creating it
	ThrowExceptionIfNotAlive();

	return *mpBoundingBox;
}

::rtl::OUString SvxPixelCtlAccessibleChild::GetName()
{
	sal_Int32 nXIndex = mnIndexInParent % mrParentWindow->GetLineCount();
	sal_Int32 nYIndex = mnIndexInParent / mrParentWindow->GetLineCount();
	
	OUString str;
	str += OUString::createFromAscii("(");
	str += OUString::valueOf(nXIndex);
	str += OUString::createFromAscii(",");
	str += OUString::valueOf(nYIndex);
// 	str += OUString::createFromAscii(",");
// 	str += OUString::valueOf(m_bPixelColorOrBG);
	str += OUString::createFromAscii(")");
	return str;
}
