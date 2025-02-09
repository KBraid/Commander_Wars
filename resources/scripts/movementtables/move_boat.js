var Constructor = function()
{
    this.getName = function()
    {
        return qsTr("Boat");
    };
    this.movementpointsTable = [["BEACH", 1],
                                ["HARBOUR", 1],
                                ["TEMPORARY_HARBOUR", 1],
                                ["FOG", 1],
                                ["SEA", 1],
                                ["LAKE", 1],
                                ["ROUGH_SEA", 2],
                                ["REAF", 2],
                                ["TELEPORTTILE", 0],
                                ["ZGATE_E_W", 1],
                                ["ZGATE_N_S", 1],
                                ["OILRIG", 1],];

    this.getMovementpoints = function(terrain, unit, currentTerrain, trapChecking = false, map)
    {
        var terrainId = terrain.getTerrainID();
        var id = terrain.getID();
        var shipBridges = true;
        if (map !== null)
        {
            shipBridges = map.getGameRules().getShipBridges();
        }
        if (shipBridges &&
            id === "BRIDGE" &&
            (terrain.getBaseTerrainID() === "SEA" ||
             terrain.getBaseTerrainID() === "LAKE"))
        {
            return 1;
        }
        else if (id === "OILRIG")
        {
            if (terrainId === "SEA" ||
                terrainId === "LAKE" )
            {
                return 1;
            }
            else
            {
                return -1;
            }
        }
        return MOVEMENTTABLE.getMovementpointsFromTable(terrain, MOVE_BOAT.movementpointsTable);
    };
};
Constructor.prototype = MOVEMENTTABLE;
var MOVE_BOAT = new Constructor();
