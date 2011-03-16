//=============================================================================
//
//   File : KvsObject_treeWidgeteItem.cpp
//   Creation date : Fri Jan 28 14:21:48 CEST 2005
//   by Tonino Imbesi(Grifisx) and Alessandro Carbone(Noldor)
//
//   This file is part of the KVIrc irc client distribution
//   Copyright (C) 2005-2008 Tonino Imbesi(Grifisx) and Alessandro Carbone(Noldor)
//
//   This program is FREE software. You can redistribute it and/or
//   modify it under the terms of the GNU General Public License
//   as published by the Free Software Foundation; either version 2
//   of the License, or (at your opinion) any later version.
//
//   This program is distributed in the HOPE that it will be USEFUL,
//   but WITHOUT ANY WARRANTY; without even the implied warranty of
//   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
//   See the GNU General Public License for more details.
//
//   You should have received a copy of the GNU General Public License
//   along with this program. If not, write to the Free Software Foundation,
//   Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
//
//=============================================================================

#include "KvsObject_treeWidgeteItem.h"
#include "KvsObject_pixmap.h"

#include "KviError.h"
#include "kvi_debug.h"
#include "KviLocale.h"
#include "KviIconManager.h"
#include <QIcon>

const int item_flags[] = {
        Qt::NoItemFlags,
	Qt::ItemIsSelectable,
	Qt::ItemIsEditable,
	Qt::ItemIsDragEnabled,
	Qt::ItemIsDropEnabled,
	Qt::ItemIsUserCheckable,
	Qt::ItemIsEnabled,
	Qt::ItemIsTristate
};

const char * const itemflags_tbl[] = {
	"noitemflag",
        "selectable",
	"editable",
	"dragEnabled",
	"dropEnabled",
	"userCheckable",
	"enabled",
	"tristate"
};

#define itemflags_num	(sizeof(itemflags_tbl) / sizeof(itemflags_tbl[0]))



/*
        @doc: listviewitem
	@keyterms:
                listview tlistviewitem class
	@title:
                listviewtitem class
	@type:
		class
	@short:
                A listviewitem class
	@inherits:
                [class]listviewitem[/class]
	@description:
                The listviewitem class implements a list view item.
                A list view item is a multi-column object capable of displaying itself in a [class]listview[/class].
                To use this class you must instantiate it with another listviewitem or a [class]listview[/class]
		as parent. The item will be automatically displayed.
		You can set the text and a pixmap in each column and you can make it checkable
                with [classfnc:listviewitem]$setCheckable[/classfnc]().
                A checkable listviewitem will display a small check mark in the first column.
	@functions:
		!fn: $setText(<column:integer>,<text:string>)
		Sets the text in column column to text, if column is a valid column number and text is different from the existing text.

		!fn: <string> $text(<column:integer>)
		Returs the text of the specified column.

		!fn: $setPixmap(<column:integer>,<pixmap:hobject or imageID>)
		Sets the pixmap in column column to pm, if pm is non-null and different from the current pixmap, and if column is non-negative.
		Pixmap can be a Kvirc imageid, an image file or a [class]pixmap[/class] object.

                !fn: $setItemEditable(<bEnabled:boolean>)
                If bEnabled is TRUE (1), this item can be in-place editable by the user; otherwise it cannot be editable in-place.

                !fn: $isItemEditable()
                Returns $true if this item is editable and $false otherwise.

		!fn: $setEnabled(<bEnabled:boolean>)
                Enables or disables the item.

		!fn: $isEnabled()
                Returns $true if this item is enabled and $false otherwise.

		!fn: $setOpen(<bOpen:boolean>)
                Opens or closes the item to show its children items.

		!fn: $isOpen()
		Returns the open state of this item

		!fn: $setCheckable(<bCheckable:boolean>)
		Makes this item checkable or not. This function should be called immediately
		after the item creation: changing this property later at runtime may have
		strange results (like the item being moved inside the list, text disappearing,
		hidden children etc... don't do it :D ).

		!fn: $isCheckable()
		Returns $true if this item is checkable and $false otherwise

		!fn: $setChecked(<bChecked:boolean>)
                Sets this item to be checked or not. [classfnc:listviewitem]$setCheckable[/classfnc]() must
		have been previously called.

		!fn: $isChecked()
                Returns the check status of this item. [classfnc:listviewitem]$setCheckable[/classfnc]() must
		have been previously called.

		!fn: $setFlags(<flag1:string>, <flag2:string>, ...)
                Sets the flags for the item to the given flags. These determine whether the item can be selected or modified. This is often used to disable an item.
                Supported flags are:
                - noitemflag : no flag sets;
                - selectable : item is selecatble;
                - editable : item is editable;
                - dragEnabled : item can dragged;
                - dropEnabled : item can used as drop target;
                - userCheckable : item is checkable;
                - enabled :item is enabled;
                - tristate : item is checkable with three separate states.


*/


//===========================================================================================

KVSO_BEGIN_REGISTERCLASS(KvsObject_treeWidgetItem,"listviewitem","object")
	KVSO_REGISTER_HANDLER_BY_NAME(KvsObject_treeWidgetItem,setText)
	KVSO_REGISTER_HANDLER_BY_NAME(KvsObject_treeWidgetItem,text)
	KVSO_REGISTER_HANDLER_BY_NAME(KvsObject_treeWidgetItem,setPixmap);
        KVSO_REGISTER_HANDLER_BY_NAME(KvsObject_treeWidgetItem,setItemEditable);
        KVSO_REGISTER_HANDLER_BY_NAME(KvsObject_treeWidgetItem,isItemEditable);
        KVSO_REGISTER_HANDLER_BY_NAME(KvsObject_treeWidgetItem,setEnabled);
        KVSO_REGISTER_HANDLER_BY_NAME(KvsObject_treeWidgetItem,isEnabled);
	KVSO_REGISTER_HANDLER_BY_NAME(KvsObject_treeWidgetItem,setOpen);
	KVSO_REGISTER_HANDLER_BY_NAME(KvsObject_treeWidgetItem,isOpen);
        KVSO_REGISTER_HANDLER_BY_NAME(KvsObject_treeWidgetItem,setCheckable);
        KVSO_REGISTER_HANDLER_BY_NAME(KvsObject_treeWidgetItem,isCheckable);
	KVSO_REGISTER_HANDLER_BY_NAME(KvsObject_treeWidgetItem,setChecked);
	KVSO_REGISTER_HANDLER_BY_NAME(KvsObject_treeWidgetItem,isChecked);
        KVSO_REGISTER_HANDLER_BY_NAME(KvsObject_treeWidgetItem,setFlags);

KVSO_END_REGISTERCLASS(KvsObject_treeWidgetItem)


KVSO_BEGIN_CONSTRUCTOR(KvsObject_treeWidgetItem,KviKvsObject)

	m_pTreeWidgetItem = 0;

KVSO_END_CONSTRUCTOR(KvsObject_treeWidgetItem)


KVSO_BEGIN_DESTRUCTOR(KvsObject_treeWidgetItem)

	if(m_pTreeWidgetItem)delete m_pTreeWidgetItem;

KVSO_END_CONSTRUCTOR(KvsObject_treeWidgetItem)

bool KvsObject_treeWidgetItem::init(KviKvsRunTimeContext * pContext,KviKvsVariantList *)
{
	if (!parentObject())
	{
		pContext->error(__tr2qs_ctx("The listviewitem cannot be parentless","objects"));
		return false;
	}
	if(parentObject()->inheritsClass("listviewitem"))
	{
		 m_pTreeWidgetItem = new KviKvsStandardTreeWidgetItem(this,((KvsObject_treeWidgetItem *)parentObject())->m_pTreeWidgetItem);
	} else {
		if(parentObject()->inheritsClass("listview"))
			m_pTreeWidgetItem = new KviKvsStandardTreeWidgetItem(this,((QTreeWidget *)parentScriptWidget()));
		else {
                        pContext->error(__tr2qs_ctx("The parent of the listviewitem must be either another listviewitem or a listview","objects"));
			return false;
		}
	}
	return true;
}

void KvsObject_treeWidgetItem::childDestroyed()
{
	if(m_pTreeWidgetItem == 0)return;
	m_pTreeWidgetItem = 0;
	die();
}

KviKvsStandardTreeWidgetItem::KviKvsStandardTreeWidgetItem(KvsObject_treeWidgetItem * ob,QTreeWidget * par)
:QTreeWidgetItem(par), m_pMasterObject(ob)
{
}

KviKvsStandardTreeWidgetItem::KviKvsStandardTreeWidgetItem(KvsObject_treeWidgetItem * ob,QTreeWidgetItem * par)
:QTreeWidgetItem(par), m_pMasterObject(ob)
{
}

KviKvsStandardTreeWidgetItem::~KviKvsStandardTreeWidgetItem()
{
	if(m_pMasterObject)m_pMasterObject->childDestroyed();
}

kvs_hobject_t KvsObject_treeWidgetItem::itemToHandle(QTreeWidgetItem * it)
{
	if(!it)return (kvs_hobject_t)0;
	KvsObject_treeWidgetItem * pObject;
	pObject = ((KviKvsStandardTreeWidgetItem *)it)->masterObject();
	if(!pObject)return (kvs_hobject_t)0;
	return pObject->handle();
}

KVSO_CLASS_FUNCTION(treeWidgetItem,setText)
{
	kvs_uint_t uCol;
	QString szText;
	KVSO_PARAMETERS_BEGIN(c)
		KVSO_PARAMETER("column",KVS_PT_UNSIGNEDINTEGER,0,uCol)
		KVSO_PARAMETER("text",KVS_PT_STRING,0,szText)
		KVSO_PARAMETERS_END(c)
	if(m_pTreeWidgetItem)
		m_pTreeWidgetItem->setText(uCol,szText);
	return true;
}


KVSO_CLASS_FUNCTION(treeWidgetItem,setItemEditable)
{
        bool bEnabled;
	KVSO_PARAMETERS_BEGIN(c)
                KVSO_PARAMETER("bEnabled",KVS_PT_BOOL,0,bEnabled)
        KVSO_PARAMETERS_END(c)
	if(m_pTreeWidgetItem)
            m_pTreeWidgetItem->setFlags(bEnabled?m_pTreeWidgetItem->flags()|Qt::ItemIsEditable:m_pTreeWidgetItem->flags()&~Qt::ItemIsEditable);
	return true;
}
KVSO_CLASS_FUNCTION(treeWidgetItem,isItemEditable)
{
        if(!m_pTreeWidgetItem)
        {
                c->returnValue()->setBoolean(false);
                return true;
        }
        c->returnValue()->setBoolean(m_pTreeWidgetItem->flags()&Qt::ItemIsEditable);
        return true;
}
KVSO_CLASS_FUNCTION(treeWidgetItem,setFlags)
{
	QStringList itemflags;
	KVSO_PARAMETERS_BEGIN(c)
		KVSO_PARAMETER("flags",KVS_PT_STRINGLIST,KVS_PF_OPTIONAL,itemflags)
	KVSO_PARAMETERS_END(c)
	int flag,sum=0;
	for ( int i=0;i<itemflags.count();i++)
	{
		flag = 0;
		for(unsigned int j = 0; j < itemflags_num; j++)
		{
			if(KviQString::equalCI(itemflags.at(i), itemflags_tbl[j]))
			{
				flag=item_flags[j];
				break;
			}
		}
		if(flag){
			if (flag==Qt::ItemIsUserCheckable)
					m_pTreeWidgetItem->setCheckState(0,Qt::Unchecked);
			sum = sum | flag;
		}
		else
                        c->warning(__tr2qs_ctx("Unknown item flag '%Q'","objects"),&itemflags.at(i));
	}
	if(m_pTreeWidgetItem)
		m_pTreeWidgetItem->setFlags((Qt::ItemFlags)sum);

	return true;
}

KVSO_CLASS_FUNCTION(treeWidgetItem,setEnabled)
{
	bool bEnabled;
	KVSO_PARAMETERS_BEGIN(c)
		KVSO_PARAMETER("bEnabled",KVS_PT_BOOL,0,bEnabled)
		KVSO_PARAMETERS_END(c)
	if(m_pTreeWidgetItem)
                m_pTreeWidgetItem->setFlags(bEnabled?m_pTreeWidgetItem->flags()|Qt::ItemIsEnabled:m_pTreeWidgetItem->flags()&~Qt::ItemIsEnabled);
	return true;
}

KVSO_CLASS_FUNCTION(treeWidgetItem,isEnabled)
{
	if(!m_pTreeWidgetItem)
	{
		c->returnValue()->setBoolean(false);
		return true;
	}
        c->returnValue()->setBoolean(m_pTreeWidgetItem->flags()&Qt::ItemIsEnabled);
	return true;
}

KVSO_CLASS_FUNCTION(treeWidgetItem,setOpen)
{
	bool bEnabled;
	KVSO_PARAMETERS_BEGIN(c)
		KVSO_PARAMETER("bEnabled",KVS_PT_BOOL,0,bEnabled)
	KVSO_PARAMETERS_END(c)
	if(m_pTreeWidgetItem)
		m_pTreeWidgetItem->setExpanded(bEnabled);
	return true;
}

KVSO_CLASS_FUNCTION(treeWidgetItem,isOpen)
{
	if(!m_pTreeWidgetItem)
	{
		c->returnValue()->setBoolean(false);
		return true;
	}
	c->returnValue()->setBoolean(m_pTreeWidgetItem->isExpanded());
	return true;
}

KVSO_CLASS_FUNCTION(treeWidgetItem,setChecked)
{
	bool bChecked;
	KVSO_PARAMETERS_BEGIN(c)
		KVSO_PARAMETER("bChecked",KVS_PT_BOOL,0,bChecked)
	KVSO_PARAMETERS_END(c)
	if(!m_pTreeWidgetItem)return true;
	((QTreeWidgetItem *)m_pTreeWidgetItem)->setCheckState(0,bChecked?Qt::Checked:Qt::Unchecked);
	return true;
}

KVSO_CLASS_FUNCTION(treeWidgetItem,isChecked)
{
	if(!m_pTreeWidgetItem)
	{
		c->returnValue()->setBoolean(false);
		return true;
	}
	c->returnValue()->setBoolean(((QTreeWidgetItem *)m_pTreeWidgetItem)->checkState(0)==Qt::Checked?1:0);
	return true;
}

KVSO_CLASS_FUNCTION(treeWidgetItem,setCheckable)
{
        bool bEnabled;
	KVSO_PARAMETERS_BEGIN(c)
                KVSO_PARAMETER("bCheckable",KVS_PT_BOOL,0,bEnabled)
	KVSO_PARAMETERS_END(c)
	if(!m_pTreeWidgetItem)return true;
        m_pTreeWidgetItem->setFlags(bEnabled?m_pTreeWidgetItem->flags()|Qt::ItemIsUserCheckable:m_pTreeWidgetItem->flags()&~Qt::ItemIsUserCheckable);
	return true;
}

KVSO_CLASS_FUNCTION(treeWidgetItem,isCheckable)
{
	if(!m_pTreeWidgetItem)
	{
		c->returnValue()->setBoolean(false);
		return true;
	}
        c->returnValue()->setBoolean(m_pTreeWidgetItem->flags()&Qt::ItemIsUserCheckable);
	return true;
}

KVSO_CLASS_FUNCTION(treeWidgetItem,text)
{
	kvs_uint_t uCol;
	KVSO_PARAMETERS_BEGIN(c)
		KVSO_PARAMETER("column",KVS_PT_UNSIGNEDINTEGER,0,uCol)
	KVSO_PARAMETERS_END(c)
	if(m_pTreeWidgetItem)
		c->returnValue()->setString(m_pTreeWidgetItem->text(uCol));
	return true;
}

KVSO_CLASS_FUNCTION(treeWidgetItem,setPixmap)
{
	kvs_uint_t uCol;
	KviKvsObject *obPixmap;
	kvs_hobject_t obHpixmap;
	KviKvsVariant * vPixmap;
	KVSO_PARAMETERS_BEGIN(c)
		KVSO_PARAMETER("column",KVS_PT_UNSIGNEDINTEGER,0,uCol)
		KVSO_PARAMETER("pixmap",KVS_PT_VARIANT,0,vPixmap)
	KVSO_PARAMETERS_END(c)
	QPixmap *pix = 0;
        if (vPixmap->isEmpty()) {m_pTreeWidgetItem->setIcon(uCol,QIcon());return true;}
	if(vPixmap->isHObject())
	{
		vPixmap->asHObject(obHpixmap);
		obPixmap=KviKvsKernel::instance()->objectController()->lookupObject(obHpixmap);
		if (!obPixmap->inheritsClass("pixmap"))
		{
                        c->warning(__tr2qs_ctx("Pixmap object or image Id required","objects"));
			return true;
		}
		pix=((KvsObject_pixmap *)obPixmap)->getPixmap();
	} else {
		QString szPix;
		vPixmap->asString(szPix);
		pix=g_pIconManager->getImage(szPix);
		if(!pix)
		{
                        c->warning(__tr2qs_ctx("Error occured: the suitable file '%Q' is not of the correct format or it is not a valid icon number.","objects"),&szPix);
			return true;
		}
	}
	m_pTreeWidgetItem->setIcon(uCol,QIcon(*pix));
	return true;
}
