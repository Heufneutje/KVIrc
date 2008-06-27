#ifndef _OBJECT_MACROS_H_
#define _OBJECT_MACROS_H_
//=========================================================================================
//
//   File : object_macros.h
//   Creation date : Sat Jun 18 2005 15:32:01 by Szymon Stefanek
//
//   This file is part of the KVirc irc client distribution
//   Copyright (C) 2005 Szymon Stefanek (pragma at kvirc dot net)
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
//   Inc. ,59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
//
//=========================================================================================

#include "kvi_kvs_kernel.h"
#include "kvi_kvs_object.h"
#include "kvi_kvs_object_class.h"
#include "kvi_kvs_object_controller.h"
#include "kvi_kvs_object_functioncall.h"

#define KVSO_DECLARE_OBJECT(__className) \
	__className(KviKvsObjectClass * pClass,KviKvsObject * pParent,const QString &szName); \
	~__className(); \
	static void registerSelf(); \
	static void unregisterSelf();
	
#define SET_OBJECT(__className) \
	__className *obj=new __className(parentScriptWidget()); \
	obj->setObjectName(getName()); \
	setObject(obj,true);
	
#define KVSO_REGISTER_HANDLER(__className,__szName,__proc) \
	g_pKvs##__className##Class->registerFunctionHandler(__szName,(KviKvsObjectFunctionHandlerProc)(KVI_PTR2MEMBER(__className::__proc)));

#define KVSO_REGISTER_STANDARD_NOTHINGRETURN_HANDLER(__className,__szName) \
	g_pKvs##__className##Class->registerStandardNothingReturnFunctionHandler(__szName);

#define KVSO_REGISTER_STANDARD_TRUERETURN_HANDLER(__className,__szName) \
	g_pKvs##__className##Class->registerStandardTrueReturnFunctionHandler(__szName);

#define KVSO_REGISTER_STANDARD_FALSERETURN_HANDLER(__className,__szName) \
	g_pKvs##__className##Class->registerStandardFalseReturnFunctionHandler(__szName);

#define KVSO_BEGIN_REGISTERCLASS(__className,__stringName,__baseClass) \
	static KviKvsObjectClass * g_pKvs##__className##Class = 0; \
	static KviKvsObject * kvs_##__className##_createInstance(KviKvsObjectClass * pClass,KviKvsObject * pParent,const QString &szName) \
	{ \
		return new __className(pClass,pParent,szName); \
	} \
	void __className::unregisterSelf() \
	{ \
		delete g_pKvs##__className##Class; \
		g_pKvs##__className##Class = 0; \
	} \
	void __className::registerSelf() \
	{ \
		KviKvsObjectClass * base = KviKvsKernel::instance()->objectController()->lookupClass(__baseClass); \
		g_pKvs##__className##Class = new KviKvsObjectClass(base,__stringName,kvs_##__className##_createInstance,true);



#define KVSO_END_REGISTERCLASS(__className) \
	}


#define KVSO_BEGIN_CONSTRUCTOR(__className,__baseClass) \
	__className::__className(KviKvsObjectClass * pClass,KviKvsObject * pParent,const QString &szName) \
	: __baseClass(pClass,pParent,szName) \
	{

#define KVSO_END_CONSTRUCTOR(__className) \
	}

#define KVSO_BEGIN_DESTRUCTOR(__className) \
	__className::~__className() \
	{

#define KVSO_END_DESTRUCTOR(__className) \
	}


#endif
