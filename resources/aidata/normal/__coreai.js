var COREAI =
        {
    infantryGroup : ["INFANTRY_GROUP",  ["INFANTRY", "MECH", "SNIPER", "MOTORBIKE", "ZCOUNIT_PARTISAN", "ZCOUNIT_COMMANDO", "ZCOUNIT_RANGER", "ZCOUNIT_AT_CYCLE"],
                                        [70,         10,     20,       30,          10,                 30,                 10,               10],
                                        40, 0, "", 0.4],
    lightTankGroup : ["LIGHT_TANK_GROUP",   ["RECON", "FLARE", "LIGHT_TANK", "ARTILLERY", "ZCOUNIT_CHAPERON", "ZCOUNIT_HOT_TANK", "ZCOUNIT_SMUGGLER", "ZCOUNIT_AUTO_TANK", "FLAK"],
                                            [5,       5,       80,           15,          15,                 15,                 15,                 30,                   10],
                                            50, 1, "", 1.0],
    mediumTankGroup : ["MEDIUM_TANK_GROUP", ["ANTITANKCANNON", "HEAVY_TANK", "ROCKETTHROWER", "ZCOUNIT_CRYSTAL_TANK", "ZCOUNIT_NEOSPIDER_TANK", "ZCOUNIT_ROYAL_GUARD", "ZCOUNIT_TANK_HUNTER"],
                                            [30,               70,           10,              40,                     40,                       40,                    40],
                                            20, 2, "", 1.0],
    heavyTankGroup : ["HEAVY_TANK_GROUP",   ["MEGATANK", "NEOTANK", "ZCOUNIT_SIEGE_CANNON", "PIPERUNNER"],
                                            [60,          30,        60,                      5],
                                            10, 3, "", 1.0],
    lightAmphibiousGroup : ["LIGHT_AMPHIBIOUS_GROUP",   ["ARTILLERYCRAFT", "HOVERCRAFT", "HOVERFLAK"],
                                                        [15,               80,           10,],
                                                        40, 1, "", 1.0],
    mediumAmphibiousGroup : ["MEDIUM_AMPHIBIOUS_GROUP", ["HEAVY_HOVERCRAFT"],
                                                        [100,],
                                                        20, 2, "", 1.0],
    lightAirGroup : ["LIGHT_AIR_GROUP", ["K_HELI", "DUSTER"],
                                        [90,       10,],
                                        30, 1, "", 1.0],
    heavyAirGroup : ["HEAVY_AIR_GROUP", ["BOMBER", "STEALTHBOMBER", "ZCOUNIT_KIROV"],
                                        [50,       25,              50],
                                        10, 3, "", 1.0],

    navalInfantryGroup : ["NAVAL_INFANTRY_GROUP",   ["GUNBOAT"],
                                                    [100],
                                                    10, 0, "", 0.05],
    lightNavalGroup : ["LIGHT_NAVAL_GROUP", ["CANNONBOAT", "TORPEDOBOAT"],
                                            [50,           50],
                                            30, 1, "", 0.2],
    mediumNavalGroup : ["MEDIUM_NAVAL_GROUP",   ["FRIGATE", "DESTROYER", "CRUISER", "SUBMARINE"],
                                                [30,        10,          30,        30],
                                                50, 2, "", 1.0],
    heavyNavalGroup : ["HEAVY_NAVAL_GROUP", ["BATTLECRUISER", "BATTLESHIP", "AIRCRAFTCARRIER"],
                                            [40,              40,           5],
                                            50, 3, "", 1.0],
    infantryTransporter : ["T_HELI", "BLACK_BOAT"],
    infantrySameIslandTransporter : ["APC"],
    infantrySearchTransporter : ["T_HELI", "BLACK_BOAT", "APC"],
    tankTransporter : ["LANDER", "TRANSPORTPLANE"],
    tankNavalTransporter : ["LANDER"],
    tankAirTransporter : ["TRANSPORTPLANE"],
    antiAirUnits : ["FLAK", "FLAK", "FLAK", "FLAK", "FIGHTER", "FIGHTER", "FIGHTER", "DUSTER", "MISSILE"],
    antiAirSeaUnits : ["CRUISER", "CRUISER", "CRUISER"],
    airUnits : ["K_HELI", "DUSTER", "BOMBER", "ZCOUNIT_KIROV", "FIGHTER", "WATERPLANE"],
    stealthAirUnits : ["STEALTHBOMBER"],
    antiAirAirUnits : ["FIGHTER", "STEALTHBOMBER", "DUSTER"],
    supplyUnits : ["APC"],
    minInfantryTransporterMapSize : 40 * 40,
    minApcResupplyDay : 15,
    minInfTransporterDay : 3,
    minTankTransporterDay : 3,
    tankTransporterDayDifference : 3,
    transporterRatio : 0.04,
    minAverageIslandSize : 0.025,

    initializeSimpleProductionSystem : function(system, ai, map, groupDistribution, buildInitialInfantry = true)
    {
        var directIndirectRatio = ai.getAiCoBuildRatioModifier();
        var player = ai.getPlayer();
        var co1 = player.getCO(0);
        var co2 = player.getCO(1);
        if (buildInitialInfantry)
        {
            system.addInitialProduction(["INFANTRY"], 6);
        }
        system.addItemToBuildDistribution(COREAI.infantryGroup[0],                                                       // group name
                                          COREAI.infantryGroup[1],                                                       // units build by the group
                                          COREAI.infantryGroup[2],                                                       // chance of the unit in this group to be build
                                          COREAI.infantryGroup[3] * groupDistribution[0] * player.getCoGroupModifier(COREAI.infantryGroup[1], system),     // army distribution for this group
                                          COREAI.infantryGroup[4],                                                       // build mode used to detect if the group is enabled or not to the army distribution
                                          COREAI.infantryGroup[5],                                                       // custom condition to enable/disable group removing it to the army distribution
                                          COREAI.infantryGroup[6]);
        var variables = system.getVariables();
        var variableNavalBattle = variables.createVariable("NAVALBATTLE");
        var naval = variableNavalBattle.readDataInt32();
        var groundModifer = 1;
        if (naval > 0)
        {
            groundModifer *= 1 / naval;
        }
        var variableAirBattle = variables.createVariable("AIRBATTLE");
        var air = variableAirBattle.readDataInt32();
        if (air > 0)
        {
            groundModifer *= 1 / air;
        }

        COREAI.addItemToBuildDistribution(system, ai, co1, co2, directIndirectRatio, COREAI.lightTankGroup, groundModifer * groupDistribution[1] * player.getCoGroupModifier(COREAI.lightTankGroup[1], system));
        COREAI.addItemToBuildDistribution(system, ai, co1, co2, directIndirectRatio, COREAI.mediumTankGroup, groundModifer * groupDistribution[2] * player.getCoGroupModifier(COREAI.mediumTankGroup[1], system));
        COREAI.addItemToBuildDistribution(system, ai, co1, co2, directIndirectRatio, COREAI.heavyTankGroup, groundModifer * groupDistribution[3] * player.getCoGroupModifier(COREAI.heavyTankGroup[1], system));
        COREAI.initAirForceDistribution(system, ai, player, co1, co2, directIndirectRatio, groupDistribution);
        COREAI.initAmphibiousDistribution(system, ai, player, co1, co2, directIndirectRatio, groupDistribution);
        if (naval > 0)
        {
            COREAI.initNavalForceDistribution(system, ai, player, co1, co2, directIndirectRatio, groupDistribution);
        }
        return true;
    },

    initAirForceDistribution : function(system, ai, player, co1, co2, directIndirectRatio, groupDistribution)
    {
        COREAI.addModifiedDistribution(system, ai, co1, co2, directIndirectRatio, COREAI.lightAirGroup, "K_HELI", groupDistribution[1] * player.getCoGroupModifier(COREAI.lightAirGroup[1], system));
        COREAI.addModifiedDistribution(system, ai, co1, co2, directIndirectRatio, COREAI.heavyAirGroup, "BOMBER", groupDistribution[3] * player.getCoGroupModifier(COREAI.heavyAirGroup[1], system));
    },

    initNavalForceDistribution : function(system, ai, player, co1, co2, directIndirectRatio, groupDistribution)
    {
        COREAI.addModifiedDistribution(system, ai, co1, co2, directIndirectRatio, COREAI.navalInfantryGroup, "GUNBOAT", groupDistribution[0] * player.getCoGroupModifier(COREAI.navalInfantryGroup[1], system));
        COREAI.addModifiedDistribution(system, ai, co1, co2, directIndirectRatio, COREAI.lightNavalGroup, "CANNONBOAT", groupDistribution[1] * player.getCoGroupModifier(COREAI.lightNavalGroup[1], system));
        COREAI.addModifiedDistribution(system, ai, co1, co2, directIndirectRatio, COREAI.mediumNavalGroup, "FRIGATE", groupDistribution[2] * player.getCoGroupModifier(COREAI.mediumNavalGroup[1], system));
        COREAI.addModifiedDistribution(system, ai, co1, co2, directIndirectRatio, COREAI.heavyNavalGroup, "BATTLECRUISER", groupDistribution[3] * player.getCoGroupModifier(COREAI.heavyNavalGroup[1], system));
    },

    initAmphibiousDistribution : function(system, ai, player, co1, co2, directIndirectRatio, groupDistribution)
    {
        COREAI.addModifiedDistribution(system, ai, co1, co2, directIndirectRatio, COREAI.lightAmphibiousGroup, "HOVERCRAFT", groupDistribution[1] * player.getCoGroupModifier(COREAI.lightAmphibiousGroup[1], system));
        COREAI.addModifiedDistribution(system, ai, co1, co2, directIndirectRatio, COREAI.mediumAmphibiousGroup, "HOVERCRAFT", groupDistribution[2] * player.getCoGroupModifier(COREAI.mediumAmphibiousGroup[1], system));
    },

    addModifiedDistribution : function(system, ai, co1, co2, directIndirectRatio, group, unitId, groupDistribution)
    {
        var dummyUnit = system.getDummyUnit(unitId);
        var mod = groupDistribution;
        if (co1 !== null)
        {
            mod += ai.getAiCoUnitMultiplier(co1, dummyUnit);
        }
        if (co2 !== null)
        {
            mod += ai.getAiCoUnitMultiplier(co2, dummyUnit);
        }
        var multiplier = 1;
        if (mod > 2)
        {
            multiplier = 3;
        }
        COREAI.addItemToBuildDistribution(system, ai, co1, co2, directIndirectRatio, group, multiplier);
    },

    addItemToBuildDistribution : function(system, ai, co1, co2, directIndirectRatio, group, distributionModifier)
    {
        var chances = [...group[2]];

        var baseValue = 0;
        if (co1 !== null)
        {
            baseValue += 5;
        }
        if (co2 !== null)
        {
            baseValue += 5;
        }

        for (var i = 0; i < chances.length; ++i)
        {
            var dummyUnit = system.getDummyUnit(group[1][i]);
            var unitRatioModifier = 1.0;
            if (directIndirectRatio > 0)
            {
                if (dummyUnit.getBaseMinRange() > 1)
                {
                    unitRatioModifier = 1 / directIndirectRatio;
                }
                else
                {
                    unitRatioModifier = directIndirectRatio;
                }
            }
            var coModifier = 1.0;
            if (baseValue > 0)
            {
                var mod = 0;
                if (co1 !== null)
                {
                    mod += ai.getAiCoUnitMultiplier(co1, dummyUnit);
                }
                if (co2 !== null)
                {
                    mod += ai.getAiCoUnitMultiplier(co2, dummyUnit);
                }
                coModifier += mod / baseValue;
            }
            chances[i] *= unitRatioModifier * coModifier;
        }
        system.addItemToBuildDistribution(group[0],                         // group name
                                          group[1],                         // units build by the group
                                          chances,                          // chance of the unit in this group to be build
                                          group[3] * distributionModifier,  // army distribution for this group
                                          group[4],                         // build mode used to detect if the group is enabled or not to the army distribution
                                          group[5],                         // custom condition to enable/disable group removing it to the army distribution
                                          group[6]);

    },
    onNewBuildQueue : function(system, ai, buildings, units, enemyUnits, enemyBuildings, map, groupDistribution)
    {
        system.resetForcedProduction();
        COREAI.forceAntiAirProduction(system, ai, units, enemyUnits);
        COREAI.forceTransporterProduction(system, ai, buildings, units, enemyUnits, enemyBuildings, groupDistribution);
        COREAI.forceApcProduction(system, ai, units);
    },

    forceTransporterProduction  : function(system, ai, buildings, units, enemyUnits, enemyBuildings, groupDistribution)
    {
        var map = ai.getMap();
        var turn = map.getCurrentDay();
        var variables = system.getVariables();
        var variableLastTransporterDay = variables.createVariable("LASTTRANSPORTERDAY");
        var lastTransporterDay = variableLastTransporterDay.readDataInt32();
        if (lastTransporterDay === 0 || turn >= COREAI.tankTransporterDayDifference + lastTransporterDay)
        {
            if (turn >= COREAI.minInfTransporterDay)
            {
                var transporterBuildings = ai.getBuildingCountsOnEnemyIslands(units, enemyBuildings);
                var infantryTransporterCount = ai.getUnitCount(units, COREAI.infantrySearchTransporter);
                var infantryTransporterCount2 = ai.getUnitCount(units, COREAI.infantryTransporter);
                if ((infantryTransporterCount === 0 ||
                    (infantryTransporterCount2 === 0 && transporterBuildings > 0)) &&
                    (COREAI.minInfantryTransporterMapSize <= map.getMapWidth() * map.getMapHeight() ||
                     transporterBuildings > 0))
                {
                    if (transporterBuildings > 0)
                    {
                        system.addForcedProduction(COREAI.infantryTransporter);
                    }
                    else
                    {
                        system.addForcedProduction(COREAI.infantryTransporter.concat(COREAI.infantrySameIslandTransporter));
                    }
                    variableLastTransporterDay.writeDataInt32(turn);
                }
            }
            if (turn >= COREAI.minTankTransporterDay)
            {                
                var tankTransporterCount = ai.getUnitCount(units, COREAI.tankTransporter);
                var tanks = COREAI.lightTankGroup[1].concat(COREAI.mediumTankGroup[1], COREAI.heavyTankGroup[1]);
                var idleUnitCount = ai.getIdleUnitCount(units, tanks, enemyUnits, enemyBuildings);
                var unitCount = units.size();
                var variableNavalBattle = variables.createVariable("NAVALBATTLE");
                var naval = variableNavalBattle.readDataInt32();
                var variableAirBattle = variables.createVariable("AIRBATTLE");                
                var air = variableAirBattle.readDataInt32();
                var hasNavalFlag = map.hasMapFlags(GameEnums.MapFilterFlags_Naval);
                var hasAirFlag = map.hasMapFlags(GameEnums.MapFilterFlags_Air);
                var hasGroundFlag = map.hasMapFlags(GameEnums.MapFilterFlags_Ground);
                if (idleUnitCount > 0 ||
                    hasNavalFlag ||
                    hasAirFlag)
                {
                    naval = 0;
                    air = 0;
                    var shareIsland = ai.shareIslandWithEnemy(units, buildings, enemyBuildings);
                    var harbourCount = buildings.getBuildingCount("HARBOUR") + enemyBuildings.getBuildingCount("HARBOUR");
                    var airportCount = buildings.getBuildingCount("AIRPORT") + enemyBuildings.getBuildingCount("AIRPORT");
                    if (harbourCount > 0)
                    {
                        if (shareIsland)
                        {
                            naval += 1;
                        }
                        else if (airportCount === 0)
                        {
                            naval += 4;
                        }
                        else
                        {
                            naval += 2;
                        }
                        if (hasNavalFlag)
                        {
                            naval += 1;
                            if (hasGroundFlag)
                            {
                                naval += 1;
                            }
                        }
                        variableNavalBattle.writeDataInt32(naval);
                    }
                    if (airportCount > 0)
                    {
                        if (shareIsland)
                        {
                            air += 1;
                        }
                        else if (harbourCount === 0)
                        {
                            air += 4;
                        }
                        else
                        {
                            air += 2;
                        }
                        if (hasAirFlag)
                        {
                            air += 1;
                            if (hasGroundFlag)
                            {
                                air += 1;
                            }
                        }
                        variableAirBattle.writeDataInt32(air);
                    }
                    system.resetBuildDistribution();
                    COREAI.initializeSimpleProductionSystem(system, ai, map, groupDistribution, false);
                }
                var buildTankTransporter = [];
                if (naval > 0)
                {
                    buildTankTransporter = buildTankTransporter.concat(COREAI.tankNavalTransporter);
                }
                if (air > 0)
                {
                    buildTankTransporter = buildTankTransporter.concat(COREAI.tankAirTransporter);
                }
                if (buildTankTransporter.length > 0 && idleUnitCount > 0)
                {
                    if (COREAI.transporterRatio * unitCount > tankTransporterCount)
                    {
                        system.addForcedProduction(buildTankTransporter);
                        variableLastTransporterDay.writeDataInt32(turn);
                    }
                }
            }
        }
    },

    forceApcProduction  : function(system, ai, units)
    {
        var map = ai.getMap();
        var turn = map.getCurrentDay();
        var lowFuelUnitCount = ai.getUnitCount(units, [], 5, 30);
        var apcCount = ai.getUnitCount(units, COREAI.supplyUnits);
        if (apcCount === 0 &&
            turn >= COREAI.minApcResupplyDay &&
            (lowFuelUnitCount > 2 ||
             COREAI.minInfantryTransporterMapSize <= map.getMapWidth() * map.getMapHeight()))
        {
            system.addForcedProduction(COREAI.supplyUnits);
        }
    },

    forceAntiAirProduction : function(system, ai, units, enemyUnits)
    {
        var antiAirUnits = COREAI.antiAirUnits;
        var variables = system.getVariables();
        var variableNavalBattle = variables.createVariable("NAVALBATTLE");
        var naval = variableNavalBattle.readDataInt32();
        if (naval > 1)
        {
           antiAirUnits = antiAirUnits.concat(COREAI.antiAirSeaUnits);
        }
        var anitAirUnitCount = ai.getUnitCount(units, antiAirUnits, 5);
        var anitAirAirUnitCount = ai.getUnitCount(units, COREAI.antiAirAirUnits, 5);
        var stealthBomberUnitCount = ai.getEnemyUnitCountNearOwnUnits(units, enemyUnits, COREAI.stealthAirUnits, 18, 5);
        var enemyAirUnits = ai.getEnemyUnitCountNearOwnUnits(units, enemyUnits, COREAI.airUnits, 18, 5);
        if ((enemyAirUnits > 0 && anitAirUnitCount === 0) ||
                (enemyAirUnits > 2 && anitAirUnitCount === 1) ||
                (anitAirUnitCount > 0 && enemyAirUnits / anitAirUnitCount >= 3))
        {
            system.addForcedProduction(antiAirUnits);
        }
        if ((stealthBomberUnitCount > 0 && anitAirAirUnitCount === 0) ||
            (stealthBomberUnitCount > 2 && anitAirAirUnitCount === 1) ||
            (anitAirAirUnitCount > 0 && stealthBomberUnitCount / anitAirAirUnitCount >= 3))
        {
            system.addForcedProduction(COREAI.antiAirAirUnits);
        }
    },

    fundsModes : [[0,     0, 0, 0],
                  [2, 12000, 0, 1],
                  [3, 7000,  0, 1],
                  [6, 5500,  0, 1],
                  [10,   0,  0, 1],
                  [3, 18000, 0, 2],
                  [0, 22000, 0, 3],
                  [6, 22000, 1, 3],
                  [6, 30000, 2, 3],],

    buildUnitSimpleProductionSystem : function(system, ai, buildings, units, enemyUnits, enemyBuildings, map)
    {
        var turn = map.getCurrentDay();
        var player = ai.getPlayer();
        var funds = player.getFunds();
        var minMode = 0;
        var maxMode = 0;
        for (var i = COREAI.fundsModes.length - 1; i >= 0; --i)
        {
            if (turn >= COREAI.fundsModes[i][0] &&
                funds >= COREAI.fundsModes[i][1])
            {
                minMode = COREAI.fundsModes[i][2];
                maxMode = COREAI.fundsModes[i][3];
                break;
            }
        }
        return system.buildNextUnit(buildings, units, minMode, maxMode, COREAI.minAverageIslandSize);
    },

    getFactoryMenuItem : function(ai, action, ids, costs, enabled, units, buildings, owner, map)
    {
        var system = ai.getSimpleProductionSystem();
        if (system.getInit() && system.getEnabled())
        {
            return system.getProductionFromList(ids, units, buildings, 0, 20, enabled); // valid index of the ids array
        }
        else
        {
            return false;
        }
    },
};
