var Constructor = function()
{
    this.getCOStyles = function()
    {
        return ["+alt", "+alt2"];
    };

    this.init = function(co, map)
    {
        co.setPowerStars(3);
        co.setSuperpowerStars(3);
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
            var animation = GameAnimationFactory.createAnimation(map, unit.getX(), unit.getY());
            var delay = globals.randInt(135, 265);
            if (animations.length < 5)
            {
                delay *= i;
            }
            if (i % 2 === 0)
            {
                animation.setSound("power7_1.wav", 1, delay);
            }
            else
            {
                animation.setSound("power7_2.wav", 1, delay);
            }
            if (animations.length < 5)
            {
                animation.addSprite("power7", -map.getImageSize() * 1.27, -map.getImageSize() * 1.27, 0, 2, delay);
                powerNameAnimation.queueAnimation(animation);
                animations.push(animation);
            }
            else
            {
                animation.addSprite("power7", -map.getImageSize() * 1.27, -map.getImageSize() * 1.27, 0, 2, delay);
                animations[counter].queueAnimation(animation);
                animations[counter] = animation;
                counter++;
                if (counter >= animations.length)
                {
                    counter = 0;
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
    };

    this.loadCOMusic = function(co, map)
    {
        if (CO.isActive(co))
        {
            switch (co.getPowerMode())
            {
            case GameEnums.PowerMode_Power:
                audio.addMusic("resources/music/cos/bh_power.mp3", 1091 , 49930);
                break;
            case GameEnums.PowerMode_Superpower:
                audio.addMusic("resources/music/cos/bh_superpower.mp3", 3161 , 37731);
                break;
            case GameEnums.PowerMode_Tagpower:
                audio.addMusic("resources/music/cos/bh_tagpower.mp3", 779 , 51141);
                break;
            default:
                audio.addMusic("resources/music/cos/flak.mp3", 9650, 78077)
                break;
            }
        }
    };

    this.getCOUnitRange = function(co, map)
    {
        return 3;
    };
    this.getCOArmy = function()
    {
        return "BH";
    };

    this.superPowerBonusLuck = 90;
    this.superPowerBonusMissfortune = 40;

    this.powerBonusLuck = 50;
    this.powerBonusMissfortune = 20;

    this.powerOffBonus = 10;
    this.powerDefBonus = 10;

    this.d2dCoZoneBonusLuck = 25;
    this.d2dCoZoneBonusMissfortune = 10;
    this.d2dCoZoneOffBonus = 10;
    this.d2dCoZoneDefBonus = 10;

    this.d2dBonusLuck = 10;
    this.d2dBonusMissfortune = 5;

    this.getBonusLuck = function(co, unit, posX, posY, map)
    {
        if (CO.isActive(co))
        {
            switch (co.getPowerMode())
            {
            case GameEnums.PowerMode_Tagpower:
            case GameEnums.PowerMode_Superpower:
                return CO_FLAK.superPowerBonusLuck;
            case GameEnums.PowerMode_Power:
                return CO_FLAK.powerBonusLuck;
            default:
                if (co.inCORange(Qt.point(posX, posY), unit))
                {
                    return CO_FLAK.d2dCoZoneBonusLuck;
                }
                break;
            }
            return CO_FLAK.d2dBonusLuck;
        }
        return 0;
    };

    this.getBonusMisfortune = function(co, unit, posX, posY, map)
    {
        if (CO.isActive(co))
        {
            switch (co.getPowerMode())
            {
            case GameEnums.PowerMode_Tagpower:
            case GameEnums.PowerMode_Superpower:
                return CO_FLAK.superPowerBonusMissfortune;
            case GameEnums.PowerMode_Power:
                return CO_FLAK.powerBonusMissfortune;
            default:
                if (co.inCORange(Qt.point(posX, posY), unit))
                {
                    return CO_FLAK.d2dCoZoneBonusMissfortune;
                }
                break;
            }
            return CO_FLAK.d2dBonusMissfortune;
        }
        return 0;
    };
    this.getOffensiveBonus = function(co, attacker, atkPosX, atkPosY,
                                      defender, defPosX, defPosY, isDefender, action, luckmode, map)
    {
        if (CO.isActive(co))
        {
            if (co.getPowerMode() > GameEnums.PowerMode_Off)
            {
                return CO_FLAK.powerOffBonus;
            }
            else if (co.inCORange(Qt.point(atkPosX, atkPosY), attacker))
            {
                return CO_FLAK.d2dCoZoneOffBonus;
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
                return CO_FLAK.powerOffBonus;
            }
            else if (co.inCORange(Qt.point(defPosX, defPosY), defender))
            {
                return CO_FLAK.d2dCoZoneDefBonus;
            }
        }
        return 0;
    };

    this.getAiCoUnitBonus = function(co, unit, map)
    {
        return 1;
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
                return ["ZCOUNIT_AT_CYCLE"];
            }
        }
        return [];
    };

    // CO - Intel
    this.getBio = function(co)
    {
        return qsTr("The strongman of the Black Hole army. Promoted form private by Hawke, who was impressed by his natural ability.");
    };
    this.getHits = function(co)
    {
        return qsTr("Meat");
    };
    this.getMiss = function(co)
    {
        return qsTr("Vegetables");
    };
    this.getCODescription = function(co)
    {
        return qsTr("High firepower, but he relies solely on strength. His shoddy technique sometimes reduces the damage his units deal.");
    };
    this.getLongCODescription = function()
    {
        var text = qsTr("\nSpecial Unit:\nAT Cycle\n") +
               qsTr("\nGlobal Effect: \nUnits have %0% more Luck and %1% Misfortune.") +
               qsTr("\n\nCO Zone Effect: \nUnits have %0% more Luck and %1% Misfortune.");
        text = replaceTextArgs(text, [CO_FLAK.d2dBonusLuck, CO_FLAK.d2dBonusMissfortune,
                                      CO_FLAK.d2dCoZoneBonusLuck, CO_FLAK.d2dCoZoneBonusMissfortune]);
        return text;
    };
    this.getPowerDescription = function(co)
    {
        var text = qsTr("Units have %0% more Luck and %1% Misfortune.");
        text = replaceTextArgs(text, [CO_FLAK.powerBonusLuck, CO_FLAK.powerBonusMissfortune]);
        return text;
    };
    this.getPowerName = function(co)
    {
        return qsTr("Brute Force");
    };
    this.getSuperPowerDescription = function(co)
    {
        var text = qsTr("Units have %0% more Luck and %1% Misfortune.");
        text = replaceTextArgs(text, [CO_FLAK.superPowerBonusLuck, CO_FLAK.superPowerBonusMissfortune]);
        return text;
    };
    this.getSuperPowerName = function(co)
    {
        return qsTr("Barbaric Blow");
    };
    this.getPowerSentences = function(co)
    {
        return [qsTr("Stay outta my way!"),
                qsTr("Grrrrrraaaaaaa! I'm outta control!"),
                qsTr("You can't hide from me! I'll hunt you down like a dog!"),
                qsTr("Nnnggrr! Braaaawrr! Smaarrrrgh!"),
                qsTr("Grr! Now you've really made me angry!"),
                qsTr("You're gonna get pummeled!")];
    };
    this.getVictorySentences = function(co)
    {
        return [qsTr("What was that? A waste of my time!"),
                qsTr("Graaa! Blaarrgggg! Smaaarrgggghhh!!"),
                qsTr("Enough weaklings footing around!")];
    };
    this.getDefeatSentences = function(co)
    {
        return [qsTr("I-I don't believe it... They were... stronger than me?"),
                qsTr("Grrr... I wanna smash your face in!!!")];
    };
    this.getName = function()
    {
        return qsTr("Flak");
    };
}

Constructor.prototype = CO;
var CO_FLAK = new Constructor();
