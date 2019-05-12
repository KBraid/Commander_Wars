var Constructor = function()
{
    this.init = function(co)
    {
        co.setPowerStars(3);
        co.setSuperpowerStars(3);
    };

    this.loadCOMusic = function(co)
    {
        // put the co music in here.
        switch (co.getPowerMode())
        {
            case GameEnums.PowerMode_Power:
                audio.addMusic("resources/music/cos/power.mp3");
                break;
            case GameEnums.PowerMode_Superpower:
                audio.addMusic("resources/music/cos/superpower.mp3");
                break;
            default:
                audio.addMusic("resources/music/cos/javier.mp3")
                break;
        }
    };

    this.activatePower = function(co)
    {
        var dialogAnimation = co.createPowerSentence();
        var powerNameAnimation = co.createPowerScreen(GameEnums.PowerMode_Power);
        dialogAnimation.queueAnimation(powerNameAnimation);

        var units = co.getPlayer().getUnits();
        var animations = [];
        var counter = 0;
        units.randomize();
        for (var i = 0; i < units.size(); i++)
        {
            var unit = units.at(i);

            var animation = GameAnimationFactory.createAnimation(unit.getX(), unit.getY());
            if (animations.length < 5)
            {
                animation.addSprite("power2", -map.getImageSize() * 1.27, -map.getImageSize() * 1.27, 0, 1.5, globals.randInt(0, 400));
                powerNameAnimation.queueAnimation(animation);
                animations.push(animation);
            }
            else
            {
                animation.addSprite("power2", -map.getImageSize() * 1.27, -map.getImageSize() * 1.27, 0, 1.5);
                animations[counter].queueAnimation(animation);
                animations[counter] = animation;
                counter++;
                if (counter >= animations.length)
                {
                    counter = 0;
                }
            }
        }
        units.remove();

        audio.clearPlayList();
        CO_JAVIER.loadCOMusic(co);
        audio.playRandom();
    };

    this.activateSuperpower = function(co, powerMode)
    {
        var dialogAnimation = co.createPowerSentence();
        var powerNameAnimation = co.createPowerScreen(powerMode);
        dialogAnimation.queueAnimation(powerNameAnimation);

        var units = co.getPlayer().getUnits();
        var animations = [];
        var counter = 0;
        units.randomize();
        for (var i = 0; i < units.size(); i++)
        {
            var unit = units.at(i);

            var animation = GameAnimationFactory.createAnimation(unit.getX(), unit.getY());
            if (animations.length < 5)
            {
                animation.addSprite("power12", -map.getImageSize() * 2, -map.getImageSize() * 2, 0, 1.5, globals.randInt(0, 400));
                powerNameAnimation.queueAnimation(animation);
                animations.push(animation);
            }
            else
            {
                animation.addSprite("power12", -map.getImageSize() * 2, -map.getImageSize() * 2, 0, 1.5);
                animations[counter].queueAnimation(animation);
                animations[counter] = animation;
                counter++;
                if (counter >= animations.length)
                {
                    counter = 0;
                }
            }
        }
        units.remove();

        audio.clearPlayList();
        CO_JAVIER.loadCOMusic(co);
        audio.playRandom();
    };

    this.getCOUnitRange = function(co)
    {
        return 2;
    };
    this.getCOArmy = function()
    {
        return "GE";
    };
    this.getOffensiveBonus = function(co, attacker, atkPosX, atkPosY,
                                 defender, defPosX, defPosY, isDefender)
    {
        var towers = co.getPlayer().getBuildingCount("TOWER");
        switch (co.getPowerMode())
        {
            case GameEnums.PowerMode_Superpower:
                return towers * 25;
            case GameEnums.PowerMode_Power:
                return towers * 15;
            default:
                if (co.inCORange(Qt.point(atkPosX, atkPosY), attacker))
                {
                    return towers * 5;
                }
                else
                {
                    return towers * 2.5;
                }
        }
    };
    this.getDeffensiveBonus = function(co, attacker, atkPosX, atkPosY,
                                 defender, defPosX, defPosY, isDefender)
    {
        var rangedAttacked = (Math.abs(atkPosX - defPosX) + Math.abs(atkPosY - defPosY) > 1);
        var towers = co.getPlayer().getBuildingCount("TOWER");
        var ret = 0;
        switch (co.getPowerMode())
        {
            case GameEnums.PowerMode_Superpower:
                if (rangedAttacked)
                {
                    ret += 60;
                }
                ret += towers * 5;
                break;
            case GameEnums.PowerMode_Power:
                if (rangedAttacked)
                {
                    ret += 40;
                }
                ret += towers * 5;
                break;
            default:
                if (rangedAttacked)
                {
                    if (co.inCORange(Qt.point(defPosX, defPosY), defender))
                    {
                        ret += 20;
                        ret += towers * 5;
                    }
                    else
                    {
                        ret += 10;
                        ret += towers * 2.5;
                    }
                }
                break;
        }
        return ret;
    };

    // CO - Intel
    this.getBio = function()
    {
        return qsTr("A Green Earth commander who values chivalry and honor above all else. Often orders his units to charge.");
    };
    this.getHits = function()
    {
        return qsTr("Honor");
    };
    this.getMiss = function()
    {
        return qsTr("Retreating");
    };
    this.getCODescription = function()
    {
        return qsTr("Units possess superior defenses vs. indirect attacks and Comtowers have a higher impact.");
    };
    this.getPowerDescription = function()
    {
        return qsTr("Improves defense vs. indirect attacks and firepower slightly rises the more Comtower he owns.");
    };
    this.getPowerName = function()
    {
        return qsTr("Tower Shield");
    };
    this.getSuperPowerDescription = function()
    {
        return qsTr("Units have even greater defenses vs. indirect attacks and firepower increases at a high rate the more Comtowers he owns.");
    };
    this.getSuperPowerName = function()
    {
        return qsTr("Tower of Power");
    };
    this.getPowerSentences = function()
    {
        return [qsTr("Away put your weapons! You shall not be needing them where you are going!"),
                qsTr("Charge into the toothy maw! For now is the time for a glorious hindspanking!"),
                qsTr("Mighty spire of communication, imbue my blade with stabby might!"),
                qsTr("Your maidenfolk shall soon howl great lamentations!"),
                qsTr("This day shall be the greatest of days, unless tomorrow is even greater!"),
                qsTr("Foe, you are mad if you seek to pierce my steely hide!")];
    };
    this.getVictorySentences = function()
    {
        return [qsTr("No sharpness can penetrate my steely hide!"),
                qsTr("Consider your hindquarters righteously spanked!"),
                qsTr("You still live, for Javier is masterful but merciful!")];
    };
    this.getDefeatSentences = function()
    {
        return [qsTr("Well done! Your reputation is well deserved."),
                qsTr("I am honored to have served with the noblest knights history has ever seen.")];
    };
    this.getName = function()
    {
        return qsTr("Javier");
    };

}

Constructor.prototype = CO;
var CO_JAVIER = new Constructor();
