// Created by Credix - Licence: https://creativecommons.org/licenses/by-nc-sa/4.0/ �
#ifndef HOOKS_H
#define HOOKS_H

#include "Common.h"
#include "../Hooks/PaintTraverse.h"
#include "../Hooks/CreateMove.h"

namespace Hooks {
	template <class T>
	T Hook(void* vtable, int index, void* hkFunc) {
		unsigned int* pVTableLocation = (unsigned int*)(*(unsigned int*)vtable);

		unsigned int* oFuncLocation = (unsigned int*)(pVTableLocation + index);
		T oFunc = (T)pVTableLocation[index];

		SIZE_T ulOldProtect = 0;
		(void)VirtualProtect(oFuncLocation, sizeof(void*), PAGE_EXECUTE_READWRITE, &ulOldProtect);
		memcpy(oFuncLocation, &hkFunc, sizeof(void*));
		(void)VirtualProtect(oFuncLocation, sizeof(void*), ulOldProtect, nullptr);
		return oFunc;
	}
	void Unhook(void* vtable, int index, void* original) {
		unsigned int* pVTableLocation = (unsigned int*)(*(unsigned int*)vtable);

		unsigned int* oFuncLocation = (unsigned int*)(pVTableLocation + index);

		SIZE_T ulOldProtect = 0;
		(void)VirtualProtect(oFuncLocation, sizeof(void*), PAGE_EXECUTE_READWRITE, &ulOldProtect);
		memcpy(oFuncLocation, &original, sizeof(void*));
		(void)VirtualProtect(oFuncLocation, sizeof(void*), ulOldProtect, nullptr);
	}

	void Init() {
		oPaintTraverse = Hook<PaintTraverse_t>(g_pPanel, 41, &hkPaintTraverse);
		oCreateMove = Hook<CreateMove_t>(g_pClientMode, 24, &hkCreateMove);
	}

	void Reset() {
		Unhook(g_pPanel, 41, oPaintTraverse);
		Unhook(g_pClientMode, 24, oCreateMove);
	}
}

#endif