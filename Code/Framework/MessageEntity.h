// - ------------------------------------------------------------------------------------------ - //
// MessageEntity //
// - ------------------------------------------------------------------------------------------ - //
#ifndef __Framework_MessageEntity_H__
#define __Framework_MessageEntity_H__
// - ------------------------------------------------------------------------------------------ - //
class cMessageEntity { 
public:
	int EndTime;
	bool HasEndTime;
	bool BreakLoop;
public:
	cMessageEntity();
	void MessageLoop();
	void GlobalInput();
	
public:
	void Work();
	void Work( const int _EndTime );
	
	virtual ~cMessageEntity()
	{
		
	}
	virtual void Draw()
	{
		
	}
	virtual void Step()
	{
		
	}
};
// - ------------------------------------------------------------------------------------------ - //
#endif // __Framework_MessageEntity_H__ // 
// - ------------------------------------------------------------------------------------------ - //
