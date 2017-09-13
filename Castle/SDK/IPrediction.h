#pragma once
struct MoveData { byte Data[256]; };
class IGameMovement
{
public:
	virtual			~IGameMovement(void) {}

	virtual void	ProcessMovement(IClientEntity *pPlayer, MoveData *pMove) = 0;
	virtual void	Reset(void) = 0;
	virtual void	StartTrackPredictionErrors(IClientEntity *pPlayer) = 0;
	virtual void	FinishTrackPredictionErrors(IClientEntity *pPlayer) = 0;
	virtual void	DiffPrint(char const *fmt, ...) = 0;

	virtual Vector const&	GetPlayerMins(bool ducked) const = 0;
	virtual Vector const&	GetPlayerMaxs(bool ducked) const = 0;
	virtual Vector const& GetPlayerViewOffset(bool ducked) const = 0;

	virtual bool			IsMovingPlayerStuck(void) const = 0;
	virtual C_BaseEntity*	GetMovingPlayer(void) const = 0;
	virtual void			UnblockPusher(IClientEntity* pPlayer, IClientEntity *pPusher) = 0;

	virtual void SetupMovementBounds(MoveData *pMove) = 0;
};

class IMoveHelper
{
public:
	void SetHost(IClientEntity* pPlayer)
	{
		typedef void(__thiscall* OriginalFn)(PVOID, IClientEntity* pPlayer);
		getvfunc< OriginalFn >(this, 1)(this, pPlayer);
	}
};

class IPrediction {
public:
	virtual void UnknownVirtual0() = 0;
	virtual void UnknownVirtual1() = 0;
	virtual void UnknownVirtual2() = 0;
	virtual void UnknownVirtual3() = 0;
	virtual void UnknownVirtual4() = 0;
	virtual void UnknownVirtual5() = 0;
	virtual void UnknownVirtual6() = 0;
	virtual void UnknownVirtual7() = 0;
	virtual void UnknownVirtual8() = 0;
	virtual void UnknownVirtual9() = 0;
	virtual void UnknownVirtual10() = 0;
	virtual void UnknownVirtual11() = 0;
	virtual void UnknownVirtual12() = 0;
	virtual void UnknownVirtual13() = 0;
	virtual void UnknownVirtual14() = 0;
	virtual void UnknownVirtual15() = 0;
	virtual void UnknownVirtual16() = 0;
	virtual void UnknownVirtual17() = 0;
	virtual void UnknownVirtual18() = 0;
	virtual void UnknownVirtual19() = 0;
	virtual void SetupMove(IClientEntity* player, CUserCmd* ucmd, void* pHelper, MoveData* move) = 0; //20
	virtual void FinishMove(IClientEntity* player, CUserCmd* ucmd, MoveData* move) = 0;
};