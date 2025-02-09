var Init =
{
    step = 0,
    playTest = 0,
    optionTestCount = 0,
    coTestStep = 0,
    currentCoTest = 0,
    steps = ["creditsTest",
             "achievementTest",
             "optionTest",
             "optionTest",
             "optionTest",
             "optionTest",
             "optionTest",
             "optionTest",
             "wikiTest",
             "shopTest",
             "coStyleTest",
             "mapEditorTest",
             "simplePlayTest",
             "simplePlayTest",
             "simplePlayTest",
             "simplePlayTest",
             "simplePlayTest",
            ],
    main = function(menu)
    {
        // disable animations
        settings.setOverworldAnimations(false);
        settings.setBattleAnimationMode(GameEnums.BattleAnimationMode_None);
        settings.setDialogAnimation(false);
        settings.setCaptureAnimation(false);
        settings.setMovementAnimations(false);
        settings.setDay2dayScreen(false);
        settings.setAnimationSpeed(100);
        settings.setBattleAnimationSpeed(100);
        settings.setDialogAnimationSpeed(100);
        settings.setCaptureAnimationSpeed(100);

        var current = Init.step;
        if (current < Init.steps.length)
        {
            Init[steps[current]](menu);
        }
        else
        {
            Init.checkNextMod(menu);
        }
    },

    checkNextMod = function(menu)
    {
        var activeMod = settings.getModString();
        var nextMod = "";

        var mods = settings.getAvailableMods();
        if (activeMod === "")
        {
            nextMod = mods[0];
        }
        else
        {
            var length = mods.length;
            for (var i = 0; i < length; ++i)
            {
                if (mods[i] === activeMod)
                {
                    if (i + 1 < length)
                    {
                        nextMod = mods[i + 1];
                    }
                    break;
                }
            }
        }
        if (nextMod !== "")
        {
            settings.removeMod(activeMod);
            settings.addMod(nextMod);
            menu.restartGame();
        }
        else
        {
            settings.removeMod(activeMod);
            menu.quitGame();
        }
    },

    creditsTest = function(menu)
    {
        menu.enterCreditsmenue();
        ++Init.step;
    },
    creditsMenu = function(menu)
    {
        menu.exitMenue();
    },
    achievementTest = function(menu)
    {
        menu.enterAchievementmenue();
        ++Init.step;
    },
    achievementMenu = function(menu)
    {
        menu.exitMenue();
    },
    optionTest = function(menu)
    {
        ++Init.optionTestCount;
        if (Init.optionTestCount === 1)
        {
            menu.enterOptionmenue("ui/options/optionvideomenu.xml");
        }
        else  if (Init.optionTestCount === 2)
        {
            menu.enterOptionmenue("ui/options/optionaudiomenu.xml");
        }
        else  if (Init.optionTestCount === 3)
        {
            menu.enterOptionmenue("ui/options/optiongameplaymenu.xml");
        }
        else  if (Init.optionTestCount === 4)
        {
            menu.enterOptionmenue("ui/options/optioncontrolsmenu.xml");
        }
        else  if (Init.optionTestCount === 5)
        {
            menu.enterOptionmenue("");
        }   
        else  if (Init.optionTestCount === 6)
        {
            menu.enterOptionmenue("ui/options/optionnetworkmenu.xml");
        }
        ++Init.step;
    },
    optionMenu = function(menu)
    {
        menu.exitMenue();
    },
    wikiTest = function(menu)
    {
        menu.enterWikimenue();
        ++Init.step;
    },
    wikiMenu = function(menu)
    {
        var wikiView = menu.getWikiView();
        wikiView.tagChanged(0);
        // test co's
        var ids = coSpriteManager.getCoIds();
        var length = ids.length;
        var i = 0;
        for (i = 0; i < length; ++i)
        {
            wikiView.showPage(ids[i]);
            globals.sleepMs(1000);
            wikiView.hideLastPage();
        }
        // test unit's
        ids = unitSpriteManager.getUnitsSorted();
        length = ids.length;
        for (i = 0; i < length; ++i)
        {
            wikiView.showPage(ids[i]);
            globals.sleepMs(1000);
            wikiView.hideLastPage();
        }
        // test terrain's
        ids = terrainSpriteManager.getTerrainsSorted();
        length = ids.length;
        for (i = 0; i < length; ++i)
        {
            wikiView.showPage(ids[i]);
            globals.sleepMs(1000);
            wikiView.hideLastPage();
        }
        // test building's
        ids = buildingSpriteManager.getLoadedBuildings();
        length = ids.length;
        for (i = 0; i < length; ++i)
        {
            wikiView.showPage(ids[i]);
            globals.sleepMs(1000);
            wikiView.hideLastPage();
        }
        // test perk's
        ids = coPerkSpriteManager.getLoadedPerks();
        length = ids.length;
        for (i = 0; i < length; ++i)
        {
            wikiView.showPage(ids[i]);
            globals.sleepMs(1000);
            wikiView.hideLastPage();
        }
        menu.exitMenue();
    },
    shopTest = function(menu)
    {
        menu.enterShopMenu();
        ++Init.step;
    },
    shopMenu = function(menu)
    {
        menu.exitMenue();
    },
    coStyleTest = function(menu)
    {
        menu.enterCOStyleMenu();
        ++Init.step;
    },
    coStyleMenu = function(menu)
    {
        menu.selectedCOIDChanged("CO_ANDY");
        menu.editCOStyle();
        menu.exitMenue();
    },
    mapEditorTest = function(menu)
    {
        menu.enterEditor();
        ++Init.step;
    },
    mapEditorMenu = function(menu)
    {
        menu.loadMap(":/maps/6_player/Stella di David.map");
        menu.resizeMap(1, 1, 1, 1);
        menu.resizeMap(-1, -1, -1, -1);
        menu.toggleGridLayout();
        menu.toggleGridLayout();
        menu.toggleMiddleCrossGrid();
        menu.toggleMiddleCrossGrid();
        menu.showResizeMap();
        menu.showSaveMap();
        menu.showLoadMap();
        menu.showEditScript();
        menu.showEditCampaign();
        menu.showImportCoWTxTMap();
        menu.showExportAwdsAws();
        menu.showImportAwdsAw4();
        menu.showImportAwByWeb();
        menu.showEditMap();
        menu.flipX();
        menu.flipY();
        menu.rotateX();
        menu.rotateY();
        menu.showRandomMap();
        menu.changePlaceSelection();
        menu.editUnits();
        menu.editTerrains();
        menu.optimizePlayers();
        menu.showEditPlayers();
        menu.showEditRules();
        menu.copy();
        menu.viewMapStats();
        menu.showExit();
        menu.exitEditor();
    },
    simplePlayTest = function(menu)
    {
        var filter = [".map"];
        currentMenu.enterSingleplayer(filter);
    },
    mapsSelection = function(menu)
    {
        if (Init.coTestStep < 3)
        {
            var ids = coSpriteManager.getCoIds();
            var co = ids[Init.currentCoTest]
            GameConsole.print("Testing co " + co + " testing co step " + Init.coTestStep.toString(), 0);
            menu.selectMap("maps/test/", "co_test.map");
            menu.buttonNext();
            menu.buttonNext();
            var selection = menu.getPlayerSelection();
            selection.selectPlayerAi(0, 0);
            selection.selectPlayerAi(1, 2);
            selection.playerCO1Changed(co, 0);
            Init.currentCoTest += 1;
            menu.startGame();
        }
        else if (Init.playTest === 0)
        {
            GameConsole.print("Testing ingame menus", 0);
            menu.selectMap("maps/2_player/", "Agitated.map");
            menu.buttonNext();
            menu.buttonNext();
            var selection = menu.getPlayerSelection();
            selection.selectPlayerAi(0, 0);
            selection.selectPlayerAi(1, 2);
            selection.playerCO1Changed("CO_RANDOM", 0);
            selection.playerCO2Changed("CO_RANDOM", 0);
            selection.playerCO1Changed("CO_RANDOM", 1);
            selection.playerCO2Changed("CO_RANDOM", 1);
            menu.startGame();
            ++Init.step;
        }
        else
        {
            GameConsole.print("Testing ai's and fog of war", 0);
            menu.selectMap("maps/2_player/", "Agitated.map");
            menu.buttonNext();
            menu.buttonNext();
            var selection = menu.getPlayerSelection();
            var map = selection.getMap();
            var gameRules = map.getGameRules();
            gameRules.setFogMode(Init.playTest - 1);
            selection.selectPlayerAi(0, 1);
            selection.selectPlayerAi(1, 2);
            selection.playerCO1Changed("CO_RANDOM", 0);
            selection.playerCO2Changed("CO_RANDOM", 0);
            selection.playerCO1Changed("CO_RANDOM", 1);
            selection.playerCO2Changed("CO_RANDOM", 1);
            menu.startGame();
            ++Init.step;
        }
    },
    gameMenu = function(menu)
    {
        if (Init.coTestStep < 3)
        {
            if (Init.coTestStep === 1)
            {
                menu.getMap().getPlayer(0).getCO(0).activatePower();
            }
            else if (Init.coTestStep === 2)
            {
                menu.getMap().getPlayer(0).getCO(0).activateSuperpower(GameEnums.PowerMode_Superpower);
            }
            menu.getMap().setIsHumanMatch(false);
            menu.changeAiForPlayer(0, GameEnums.AiTypes_Normal);
            var ids = coSpriteManager.getCoIds();
            if (Init.currentCoTest >= ids.length)
            {
                Init.coTestStep += 1;
                Init.currentCoTest = 0;
            }
        }
        else if (Init.playTest === 0)
        {
            GameConsole.print("Showing all ingame menus", 0);
            menu.victoryInfo();
            menu.showCOInfo();
            menu.showGameInfo(0);
            menu.showXmlFileDialog("ui/options/optiongameplaymenu.xml", true);
            menu.showXmlFileDialog("ui/options/optionaudiomenu.xml", true);
            menu.showAttackLog(0);
            menu.showRules();
            menu.showUnitInfo(0);
            menu.showUnitStatistics(0);
            menu.showExitGame();
            menu.showSurrenderGame();
            menu.showSaveAndExitGame();
            var wikiView = menu.showWiki();
            wikiView.tagChanged(0);
            wikiView.showPage("CO_ANDY");
            wikiView.showPage("MECH");
            wikiView.showPage("PLAINS");
            wikiView.showPage("HQ");
            menu.exitGameDelayed();
        }
    },
    onVictory = function(menu)
    {
        GameConsole.print("On Victory", 0);
        ++Init.playTest;
        menu.exitMenue();
    },
}
