// Author: Valve Corporation
// Licence: https://github.com/ValveSoftware/source-sdk-2013/blob/master/LICENSE
#ifndef ICLIENTTHINKABLE_H
#define ICLIENTTHINKABLE_H

class ICollideable;

class CClientThinkHandlePtr;
typedef CClientThinkHandlePtr* ClientThinkHandle_t;

class CBaseHandle;
class C_BaseEntity;
class IClientThinkable;

class IHandleEntity
{
public:
	virtual ~IHandleEntity() {}
	virtual void SetRefEHandle(const CBaseHandle &handle) = 0;
	virtual const CBaseHandle& GetRefEHandle() const = 0;
};

class CBaseHandle
{
	friend class CBaseEntityList;
public:
	CBaseHandle() {

	}
	CBaseHandle(const CBaseHandle &other) {

	}
	CBaseHandle(unsigned long value) {

	}
	CBaseHandle(int iEntry, int iSerialNumber) {

	}
	void Init(int iEntry, int iSerialNumber) {
		typedef void(__thiscall* Fn)(void*, int, int);
		Utils::GetVFunc<Fn>(this, 0)(this, iEntry, iSerialNumber);
	}
	void Term() {
		typedef void(__thiscall* Fn)(void*);
		Utils::GetVFunc<Fn>(this, 1)(this);
	}
	bool IsValid() {
		typedef bool(__thiscall* Fn)(void*);
		Utils::GetVFunc<Fn>(this, 2)(this);
	}
	int GetEntryIndex() const;
	int GetSerialNumber() const;
	int ToInt() const;
	bool operator !=(const CBaseHandle &other) const;
	bool operator ==(const CBaseHandle &other) const;
	bool operator ==(const IHandleEntity* pEnt) const;
	bool operator !=(const IHandleEntity* pEnt) const;
	bool operator <(const CBaseHandle &other) const;
	bool operator <(const IHandleEntity* pEnt) const;
	const CBaseHandle& operator=(const IHandleEntity *pEntity);
	const CBaseHandle& Set(const IHandleEntity *pEntity);
	IHandleEntity* Get() const;
protected:
	unsigned long	m_Index;
};

class IClientUnknown : public IHandleEntity
{
public:
	virtual ICollideable*		GetCollideable() = 0;
	virtual class IClientNetworkable*	GetClientNetworkable() = 0;
	virtual class IClientRenderable*	GetClientRenderable() = 0;
	virtual class IClientEntity*		GetIClientEntity() = 0;
	virtual C_BaseEntity*		GetBaseEntity() {
		typedef C_BaseEntity*(__thiscall* Fn)(void*);
		return Utils::GetVFunc<Fn>(this, 4)(this);
	}
	virtual IClientThinkable*	GetClientThinkable() = 0;
};

class IClientThinkable
{
public:
	virtual IClientUnknown*		GetIClientUnknown() = 0;
	virtual void				ClientThink() = 0;
	virtual ClientThinkHandle_t	GetThinkHandle() = 0;
	virtual void				SetThinkHandle(ClientThinkHandle_t hThink) = 0;
	virtual void				Release() = 0;
};


#endif