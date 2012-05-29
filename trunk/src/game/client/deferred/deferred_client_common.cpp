
#include "cbase.h"
#include "deferred/deferred_shared_common.h"

void ConVarCallbackShadowRes( IConVar *var, const char *pOldValue, float flOldValue )
{
	InitDeferredRTs( false );
}

ConVar deferred_rt_shadowspot_res( "deferred_rt_shadowspot_res", "1024", 0, "", ConVarCallbackShadowRes );
ConVar deferred_rt_shadowpoint_res( "deferred_rt_shadowpoint_res", "1024", 0, "", ConVarCallbackShadowRes );

ConVar deferred_lightmanager_debug( "deferred_lightmanager_debug", "0" );

ConVar deferred_override_globalLight_enable( "deferred_override_globalLight_enable", "0" );
ConVar deferred_override_globalLight_shadow_enable( "deferred_override_globalLight_shadow_enable", "1" );
ConVar deferred_override_globalLight_diffuse( "deferred_override_globalLight_diffuse", "1 1 1" );
ConVar deferred_override_globalLight_ambient_high( "deferred_override_globalLight_ambient_high", "0 0.04 0.08" );
ConVar deferred_override_globalLight_ambient_low( "deferred_override_globalLight_ambient_low", "0 0.07 0.09" );

void OnCookieTableChanged( void *object, INetworkStringTable *stringTable, int stringNumber, const char *newString, void const *newData )
{
	if ( !newString || Q_strlen( newString ) < 1 )
		return;

	GetLightingManager()->OnCookieStringReceived( newString, stringNumber );
}

void CalcBoundaries( Vector *list, const int &num, Vector &min, Vector &max )
{
	Assert( num > 0 );

	min = *list;
	max = *list;

	for ( int i = 1; i < num; i++ )
	{
		for ( int x = 0; x < 3; x++ )
		{
			min[ x ] = MIN( min[ x ], list[ i ][ x ] );
			max[ x ] = MAX( max[ x ], list[ i ][ x ] );
		}
	}
}