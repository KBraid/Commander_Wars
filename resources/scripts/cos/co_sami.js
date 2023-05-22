var Constructor = function()
{
    this.getCOStyles = function()
    {
        return ["+alt", "+alt2", "+alt3"];
    };

    this.init = function(co, map)
    {
        co.setPowerStars(3);
        co.setSuperpowerStars(6);
    };

    this.loadCOMusic = function(co, map)
    {
        if (CO.isActive(co))
        {
            switch (co.getPowerMode())
            {
            case GameEnums.PowerMode_Power:
                audio.addMusic("resources/music/cos/power.mp3", 992, 45321);
                break;
            case GameEnums.PowerMode_Superpower:
                audio.addMusic("resources/music/cos/superpower.mp3", 1505, 49515);
                break;
            case GameEnums.PowerMode_Tagpower:
                audio.addMusic("resources/music/cos/tagpower.mp3", 14611, 65538);
                break;
            default:
                audio.addMusic("resources/music/cos/sami.mp3", 1934, 62918);
                break;
            }
        }
    };

    this.activatePower = function(co, map)
    {
        var dialogAnimation = co.createPowerSentence();
        var powerNameAnimation = co.createPowerScreen(GameEnums.PowerMode_Power);
        dialogAnimation.queueAnimation(powerNameAnimation);

        var units = co.getOwner().getUnits();
        var animations = [];
        var counter = 0;
        units.randomize();
        for (var i = 0; i < units.size(); i++)
        {
            var unit = units.at(i);
            if (unit.getUnitType() === GameEnums.UnitType_Infantry)
            {
                var animation = GameAnimationFactory.createAnimation(map, unit.getX(), unit.getY());
                var delay = globals.randInt(135, 265);
                if (animations.length < 5)
                {
                    delay *= i;
                }
                if (i % 2 === 0)
                {
                    animation.setSound("power10_1.wav", 1, delay);
                }
                else
                {
                    animation.setSound("power10_2.wav", 1, delay);
                }
                if (animations.length < 5)
                {
                    animation.addSprite("power10", -map.getImageSize() * 1.27, -map.getImageSize() * 1.27, 0, 2, delay);
                    powerNameAnimation.queueAnimation(animation);
                    animations.push(animation);
                }
                else
                {
                    animation.addSprite("power10", -map.getImageSize() * 1.27, -map.getImageSize() * 1.27, 0, 2, delay);
                    animations[counter].queueAnimation(animation);
                    animations[counter] = animation;
                    counter++;
                    if (counter >= animations.length)
                    {
                        counter = 0;
                    }
                }
            }
        }
    };

    this.activateSuperpower = function(co, powerMode, map)
    {
        var dialogAnimation = co.createPowerSentence();
        var powerNameAnimation = co.createPowerScreen(powerMode);
        powerNameAnimation.queueAnimationBefore(dialogAnimation);

        var units = co.getOwner().getUnits();
        var animations = [];
        var counter = 0;
        units.randomize();
        for (var i = 0; i < units.size(); i++)
        {
            var unit = units.at(i);
            if (unit.getUnitType() === GameEnums.UnitType_Infantry)
            {
                var animation = GameAnimationFactory.createAnimation(map, unit.getX(), unit.getY());
                var delay = globals.randInt(135, 265);
                if (animations.length < 7)
                {
                    delay *= i;
                }
                if (i % 2 === 0)
                {
                    animation.setSound("power12_1.wav", 1, delay);
                }
                else
                {
                    animation.setSound("power12_2.wav", 1, delay);
                }
                if (animations.length < 7)
                {
                    animation.addSprite("power12", -map.getImageSize() * 2, -map.getImageSize() * 2, 0, 2, delay);
                    powerNameAnimation.queueAnimation(animation);
                    animations.push(animation);
                }
                else
                {
                    animation.addSprite("power12", -map.getImageSize() * 2, -map.getImageSize() * 2, 0, 2, delay);
                    animations[counter].queueAnimation(animation);
                    animations[counter] = animation;
                    counter++;
                    if (counter >= animations.length)
                    {
                        counter = 0;
                    }
                }
            }
        }
    };

    this.getCOUnitRange = function(co, map)
    {
        return 3;
    };
    this.getCOArmy = function()
    {
        return "OS";
    };

    this.superPowerOffBonus = 80;
    this.superpowerMovementPoints = 2;
    this.superpowerCaptureMultiplier = 20;

    this.powerOffBonus = 50;
    this.powerDefBonus = 10;
    this.powerBaseOffBonus = 10;
    this.powerMovementPoints = 1;
    this.powerMovementCostModifier = 0;

    this.d2dCoZoneOffBonus = 50;
    this.d2dCoZoneBaseOffBonus = 10;
    this.d2dCoZoneDefBonus = 10;

    this.d2dInfOffBonus = 20;
    this.d2dInfDefBonus = 0;
    this.d2dDirectOffBonus = -10;
    this.d2dCaptureMultiplier = 0.5;
    this.d2dTransporterMovementPoints = 1;

    this.getOffensiveBonus = function(co, attacker, atkPosX, atkPosY,
                                      defender, defPosX, defPosY, isDefender, action, luckmode, map)
    {
        if (CO.isActive(co))
        {
            switch (co.getPowerMode())
            {
            case GameEnums.PowerMode_Tagpower:
            case GameEnums.PowerMode_Superpower:
                if (attacker.getUnitType() === GameEnums.UnitType_Infantry)
                {
                    return CO_SAMI.superPowerOffBonus;
                }
                else if (attacker.getBaseMaxRange() === 1)
                {
                    return CO_SAMI.powerBaseOffBonus + CO_SAMI.d2dDirectOffBonus;
                }
                return CO_SAMI.powerBaseOffBonus;
            case GameEnums.PowerMode_Power:
                if (attacker.getUnitType() === GameEnums.UnitType_Infantry)
                {
                    return 50;
                }
                else if (attacker.getBaseMaxRange() === 1)
                {
                    return CO_SAMI.powerBaseOffBonus + CO_SAMI.d2dDirectOffBonus;
                }
                return CO_SAMI.powerBaseOffBonus;
            default:                
                if (co.inCORange(Qt.point(atkPosX, atkPosY), attacker))
                {
                    if (attacker.getUnitType() === GameEnums.UnitType_Infantry)
                    {
                        return CO_SAMI.d2dCoZoneOffBonus;
                    }
                    else if (attacker.getBaseMaxRange() === 1)
                    {
                        return CO_SAMI.d2dCoZoneBaseOffBonus + CO_SAMI.d2dDirectOffBonus;
                    }
                    return CO_SAMI.d2dCoZoneBaseOffBonus;
                }
                else if (attacker.getUnitType() === GameEnums.UnitType_Infantry)
                {
                    return CO_SAMI.d2dInfOffBonus;
                }
                break;
            }
            if (attacker.getBaseMaxRange() === 1)
            {
                return CO_SAMI.d2dDirectOffBonus;
            }
        }
        return 0;
    };
    this.getDeffensiveBonus = function(co, attacker, atkPosX, atkPosY,
                                       defender, defPosX, defPosY, isAttacker, action, luckmode, map)
    {
        if (CO.isActive(co))
        {
            if (co.getPowerMode() > GameEnums.PowerMode_Off)
            {
                return CO_SAMI.powerDefBonus + CO_SAMI.d2dInfDefBonus;
            }            
            else if (co.inCORange(Qt.point(defPosX, defPosY), defender))
            {
                return CO_SAMI.d2dCoZoneDefBonus;
            }
            else if (defender.getUnitType() === GameEnums.UnitType_Infantry)
            {
                return CO_SAMI.d2dInfDefBonus;
            }
        }
        return 0;
    };
    this.getCaptureBonus = function(co, unit, posX, posY, map)
    {
        if (CO.isActive(co))
        {
            var hp = unit.getHpRounded();
            if (co.getPowerMode() === GameEnums.PowerMode_Superpower ||
                    co.getPowerMode() === GameEnums.PowerMode_Tagpower)
            {
                return hp * CO_SAMI.superpowerCaptureMultiplier;
            }
            else
            {
                return hp * CO_SAMI.d2dCaptureMultiplier;
            }
        }
        return 0;
    };

    this.getMovementpointModifier = function(co, unit, posX, posY, map)
    {
        if (CO.isActive(co))
        {
            if (unit.isTransporter())
            {
                return CO_SAMI.d2dTransporterMovementPoints;
            }
            if (unit.getUnitType() === GameEnums.UnitType_Infantry)
            {
                switch (co.getPowerMode())
                {
                case GameEnums.PowerMode_Tagpower:
                case GameEnums.PowerMode_Superpower:
                    return CO_SAMI.superpowerMovementPoints;
                case GameEnums.PowerMode_Power:
                    return CO_SAMI.powerMovementPoints;
                default:
                    return 0;
                }
            }
        }
        return 0;
    };
    this.getMovementcostModifier = function(co, unit, posX, posY, map)
    {
        if (co.getIsCO0() === true)
        {
            if (unit.getOwner() === co.getOwner() &&
                unit.getUnitType() === GameEnums.UnitType_Infantry)
            {
                switch (co.getPowerMode())
                {
                case GameEnums.PowerMode_Tagpower:
                case GameEnums.PowerMode_Superpower:
                case GameEnums.PowerMode_Power:
                    return CO_SAMI.powerMovementCostModifier;
                default:
                    return 0;
                }
            }
        }
        return 0;
    };
    this.getAiCoUnitBonus = function(co, unit, map)
    {
        if (unit.getUnitID !== "INFANTRY")
        {
            if (unit.getUnitType() === GameEnums.UnitType_Infantry)
            {
                return 8;
            }
            else if (unit.getBaseMaxRange() === 1)
            {
                return -1;
            }
        }
        return 2;
    };
    this.getAiCoBuildRatioModifier = function(co, map)
    {
        return 0.5;
    };
    this.getCOUnits = function(co, building, map)
    {
        if (CO.isActive(co))
        {
            var buildingId = building.getBuildingID();
            if (buildingId === "FACTORY" ||
                    buildingId === "TOWN" ||
                    buildingId === "HQ" ||
                    buildingId === "FORTHQ")
            {
                return ["ZCOUNIT_COMMANDO"];
            }
        }
        return [];
    };

    // CO - Intel
    this.getBio = function(co)
    {
        return qsTr("A strong-willed Orange Star special forces captain who loves long hair. Despite having short hair. Whatever, IS.");
    };
    this.getHits = function(co)
    {
        return qsTr("Chocolate");
    };
    this.getMiss = function(co)
    {
        return qsTr("Cowards");
    };
    this.getCODescription = function(co)
    {
        return qsTr("As an infantry specialist, her foot soldiers do more damage and capture faster. Non-infantry direct-combat units have weaker firepower.");
    };
    this.getLongCODescription = function()
    {
        var text = qsTr("\nSpecial Unit:\nCommando\n") +
               qsTr("\nGlobal Effect: \nTransporter have %0 more movement point and infantries have increased capture rate by %1% and firepower by %2% and defence by %3%. Non-infantry direct-combat units have %4% weaker firepower.") +
               qsTr("\n\nCO Zone Effect: \nInfantry Units have %5% increased firepower.");
        text = replaceTextArgs(text, [CO_SAMI.d2dTransporterMovementPoints, CO_SAMI.d2dCaptureMultiplier * 100, CO_SAMI.d2dInfOffBonus, CO_SAMI.d2dInfDefBonus, CO_SAMI.d2dDirectOffBonus]);
        return text;
    };
    this.getPowerDescription = function(co)
    {
        var text = qsTr("Infantry units receive a movement bonus of %0 space. Their attack also increases by %1.");
        text = replaceTextArgs(text, [CO_SAMI.powerMovementPoints, CO_SAMI.powerOffBonus]);
        return text;
    };
    this.getPowerName = function(co)
    {
        return qsTr("Double Time");
    };
    this.getSuperPowerDescription = function(co)
    {
        var text = qsTr("All foot soldiers gain a capture %0 capture rate. Their movement is increased by %1 spaces and their attack increases by %2.");
        text = replaceTextArgs(text, [CO_SAMI.superpowerCaptureMultiplier * 100, CO_SAMI.superpowerMovementPoints, CO_SAMI.superPowerOffBonus]);
        return text;
    };
    this.getSuperPowerName = function(co)
    {
        return qsTr("Victory March");
    };
    this.getPowerSentences = function(co)
    {
        return [qsTr("You're not bad!  Now it's my turn!"),
                qsTr("All right!  Time to end this!"),
                qsTr("Infantry... Assault!"),
                qsTr("Ready or not, here I come!"),
                qsTr("All right, it's make-or-break time!"),
                qsTr("Move out, grunts!")];
    };
    this.getVictorySentences = function(co)
    {
        return [qsTr("Mission accomplished! Awaiting orders!"),
                qsTr("Commandos always complete their mission."),
                qsTr("Score one for the grunts!")];
    };
    this.getDefeatSentences = function(co)
    {
        return [qsTr("Things would be easier if we had more infantry units..."),
                qsTr("Next time's for real. I won't lose focus.")];
    };
    this.getName = function()
    {
        return qsTr("Sami");
    };
}

Constructor.prototype = CO;
var CO_SAMI = new Constructor();
