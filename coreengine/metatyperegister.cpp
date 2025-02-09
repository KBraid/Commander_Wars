#include <QEasingCurve>

#include "coreengine/metatyperegister.h"

#include "3rd_party/oxygine-framework/oxygine/KeyEvent.h"

#include "coreengine/scriptvariable.h"
#include "coreengine/scriptvariables.h"
#include "coreengine/scriptvariablefile.h"
#include "coreengine/audiomanager.h"

#include "ai/productionSystem/simpleproductionsystem.h"
#include "ai/heavyai.h"
#include "ai/normalai.h"
#include "ai/influencefrontmap.h"

#include "menue/basegamemenu.h"
#include "menue/victorymenue.h"
#include "menue/mainwindow.h"
#include "menue/creditsmenue.h"
#include "menue/gamemenue.h"
#include "menue/mapselectionmapsmenue.h"
#include "menue/campaignmenu.h"
#include "menue/editormenue.h"
#include "menue/achievementmenu.h"
#include "menue/optionmenue.h"
#include "menue/basemenu.h"
#include "menue/movementplanner.h"
#include "menue/generatormenu.h"

#include "multiplayer/multiplayermenu.h"
#include "multiplayer/networkgamedataview.h"

#include "ui_reader/uifactory.h"
#include "ui_reader/createdgui.h"

#include "network/networkgame.h"
#include "network/mainserver.h"
#include "network/automatchmaker.h"

#include "game/terrain.h"
#include "game/player.h"
#include "game/building.h"
#include "game/unit.h"
#include "game/co.h"
#include "game/gameaction.h"
#include "game/gameanimation/gameanimation.h"
#include "game/gameanimation/gameanimationwalk.h"
#include "game/gameanimation/gameanimationcapture.h"
#include "game/gameanimation/gameanimationdialog.h"
#include "game/gameanimation/gameanimationpower.h"
#include "game/gameanimation/gameanimationnextday.h"
#include "game/victoryrule.h"
#include "game/gamerules.h"
#include "game/gamerule.h"
#include "game/weather.h"
#include "game/terrainfindingsystem.h"
#include "game/campaign.h"
#include "game/gamescript.h"
#include "game/GameEnums.h"
#include "game/gamerecording/gamerecorder.h"
#include "game/gamerecording/playerrecord.h"
#include "game/gamerecording/specialevent.h"
#include "game/gamerecording/daytodayrecord.h"

#include "game/ui/customcoboostinfo.h"
#include "game/ui/movementplanneraddin.h"

#include "game/jsData/terrainflowdata.h"
#include "game/jsData/campaignmapdata.h"

#include "wiki/wikidatabase.h"
#include "wiki/wikiview.h"

#include "objects/playerselection.h"
#include "objects/dialogs/mapSelection/mapselectionfilterdialog.h"
#include "objects/dialogs/editor/mapeditdialog.h"
#include "objects/dialogs/gamepadinfo.h"
#include "objects/dialogs/customdialog.h"

#include "objects/base/checkbox.h"
#include "objects/base/colorselector.h"
#include "objects/base/dropdownmenu.h"
#include "objects/base/dropdownmenubase.h"
#include "objects/base/dropdownmenucolor.h"
#include "objects/base/dropdownmenusprite.h"
#include "objects/base/focusableobject.h"
#include "objects/base/label.h"
#include "objects/base/multislider.h"
#include "objects/base/passwordbox.h"
#include "objects/base/slider.h"
#include "objects/base/spinbox.h"
#include "objects/base/tableview.h"
#include "objects/base/textbox.h"
#include "objects/base/textinput.h"
#include "objects/base/timespinbox.h"
#include "objects/base/tooltip.h"

#include "gameinput/cursordata.h"
#include "gameinput/basegameinputif.h"

#include "ingamescriptsupport/events/scriptevent.h"
#include "ingamescriptsupport/conditions/scriptcondition.h"

#include "resource_management/cospritemanager.h"
#include "resource_management/terrainmanager.h"
#include "resource_management/buildingspritemanager.h"
#include "resource_management/coperkmanager.h"
#include "resource_management/unitspritemanager.h"
#include "resource_management/gamerulemanager.h"

void MetaTypeRegister::registerInterfaceData()
{
    // qt metatypes we need this for js and signal slot stuff
    qRegisterMetaType<NetworkInterface::NetworkSerives>("NetworkInterface::NetworkSerives");
    qRegisterMetaType<VictoryMenue::GraphModes>("VictoryMenue::GraphModes");
    qRegisterMetaType<GameEnums::Alliance>("GameEnums::Alliance");
    qRegisterMetaType<GameEnums::UnitRanks>("GameEnums::UnitRanks");
    qRegisterMetaType<GameEnums::PowerMode>("GameEnums::PowerMode");
    qRegisterMetaType<GameEnums::RocketTarget>("GameEnums::RocketTarget");
    qRegisterMetaType<GameEnums::DefeatType>("GameEnums::DefeatType");
    qRegisterMetaType<GameEnums::Directions>("GameEnums::Directions");
    qRegisterMetaType<GameEnums::AIQuestionType>("GameEnums::AIQuestionType");
    qRegisterMetaType<GameEnums::Fog>("GameEnums::Fog");
    qRegisterMetaType<GameEnums::COMood>("GameEnums::COMood");
    qRegisterMetaType<GameEnums::LuckDamageMode>("GameEnums::LuckDamageMode");
    qRegisterMetaType<GameEnums::GameRecord_SpecialEvents>("GameEnums::GameRecord_SpecialEvents");
    qRegisterMetaType<GameEnums::GameAi>("GameEnums::GameAi");
    qRegisterMetaType<GameEnums::BattleAnimationType>("GameEnums::BattleAnimationType");
    qRegisterMetaType<GameEnums::BuildingTarget>("GameEnums::BuildingTarget");
    qRegisterMetaType<GameEnums::BattleAnimationMode>("GameEnums::BattleAnimationMode");
    qRegisterMetaType<GameEnums::UnitType>("GameEnums::UnitType");
    qRegisterMetaType<GameEnums::VisionType>("GameEnums::VisionType");
    qRegisterMetaType<GameEnums::AiTypes>("GameEnums::AiTypes");
    qRegisterMetaType<GameEnums::Recoloring>("GameEnums::Recoloring");
    qRegisterMetaType<GameEnums::COInfoPosition>("GameEnums::COInfoPosition");
    qRegisterMetaType<GameEnums::WeaponType>("GameEnums::WeaponType");
    qRegisterMetaType<GameEnums::ShopItemType>("GameEnums::ShopItemType");
    qRegisterMetaType<GameEnums::PowerGainZone>("GameEnums::PowerGainZone");
    qRegisterMetaType<GameEnums::PowerGainMode>("GameEnums::PowerGainMode");
    qRegisterMetaType<GameEnums::DamageFormula>("GameEnums::DamageFormula");
    qRegisterMetaType<QEasingCurve::Type>("QEasingCurve::Type");
    qRegisterMetaType<GameConsole::eLogLevels>("Console::eLogLevels");
    qRegisterMetaType<Mainapp::StartupPhase>("Mainapp::StartupPhase");
    qRegisterMetaType<spScriptEvent>("spScriptEvent");
    qRegisterMetaType<spScriptCondition>("spScriptCondition");
    qRegisterMetaType<oxygine::spActor>("oxygine::spActor");
    qRegisterMetaType<oxygine::spResAnim>("oxygine::spResAnimf");
    qRegisterMetaType<oxygine::KeyEvent>("oxygine::KeyEvent");
    qRegisterMetaType<oxygine::MouseButton>("oxygine::MouseButton");
    qRegisterMetaType<QVector<float>>("QVector<float>");
    qRegisterMetaType<QVector<qint32>>("QVector<qint32>");
    qRegisterMetaType<QLocalSocket::LocalSocketError>("QLocalSocket::LocalSocketError");
    qRegisterMetaType<QAbstractSocket::SocketError>("QAbstractSocket::SocketError");
    qRegisterMetaType<QAbstractSocket::SocketState>("QAbstractSocket::SocketState");
    qRegisterMetaType<spGameAction>("spGameAction");
    qRegisterMetaType<MapEditDialog::MapEditInfo>("MapEditDialog::MapEditInfo");

    // interface
    qmlRegisterInterface<Terrain>("Terrain", 1);
    qmlRegisterInterface<Player>("Player", 1);
    qmlRegisterInterface<Building>("Building", 1);
    qmlRegisterInterface<Unit>("Unit", 1);
    qmlRegisterInterface<CO>("CO", 1);
    qmlRegisterInterface<GameAction>("GameAction", 1);
    qmlRegisterInterface<GameAnimation>("GameAnimation", 1);
    qmlRegisterInterface<GameAnimationWalk>("GameAnimationWalk", 1);
    qmlRegisterInterface<GameAnimationCapture>("GameAnimationCapture", 1);
    qmlRegisterInterface<GameAnimationDialog>("GameAnimationDialog", 1);
    qmlRegisterInterface<GameAnimationPower>("GameAnimationPower", 1);
    qmlRegisterInterface<GameAnimationNextDay>("GameAnimationNextDay", 1);
    qmlRegisterInterface<QmlVectorPoint>("QmlVectorPoint", 1);
    qmlRegisterInterface<QmlVectorUnit>("QmlVectorUnit", 1);
    qmlRegisterInterface<QmlVectorBuilding>("QmlVectorBuilding", 1);
    qmlRegisterInterface<Mainapp>("Mainapp", 1);
    qmlRegisterInterface<CursorData>("CursorData", 1);
    qmlRegisterInterface<VictoryRule>("VictoryRule", 1);
    qmlRegisterInterface<GameRules>("GameRules", 1);
    qmlRegisterInterface<GameRule>("GameRule", 1);
    qmlRegisterInterface<ScriptVariable>("ScriptVariable", 1);
    qmlRegisterInterface<ScriptVariables>("ScriptVariables", 1);
    qmlRegisterInterface<ScriptVariableFile>("ScriptVariableFile", 1);
    qmlRegisterInterface<Weather>("Weather", 1);
    qmlRegisterInterface<TerrainFindingSystem>("TerrainFindingSystem", 1);
    qmlRegisterInterface<GameRecorder>("GameRecorder", 1);
    qmlRegisterInterface<GameScript>("GameScript", 1);
    qmlRegisterInterface<Campaign>("Campaign", 1);
    qmlRegisterInterface<BaseGameInputIF>("BaseGameInputIF", 1);
    qmlRegisterInterface<Settings>("Settings", 1);
    qmlRegisterInterface<Wikipage>("Wikipage", 1);
    qmlRegisterInterface<HeavyAi>("HeavyAi", 1);
    qmlRegisterInterface<SimpleProductionSystem>("SimpleProductionSystem", 1);
    qmlRegisterInterface<InfluenceFrontMap>("InfluenceFrontMap", 1);
    qmlRegisterInterface<InfluenceInfo>("InfluenceInfo", 1);

    qmlRegisterInterface<NormalAi>("NormalAi", 1);
    qmlRegisterInterface<NeuralNetwork>("NeuralNetwork", 1);
    qmlRegisterInterface<NetworkGame>("NetworkGame", 1);
    qmlRegisterInterface<PlayerSelection>("PlayerSelection", 1);
    qmlRegisterInterface<COSpriteManager>("COSpriteManager", 1);
    qmlRegisterInterface<UnitSpriteManager>("UnitSpriteManager", 1);
    qmlRegisterInterface<BuildingSpriteManager>("BuildingSpriteManager", 1);
    qmlRegisterInterface<GameRuleManager>("GameRuleManager", 1);
    qmlRegisterInterface<TerrainManager>("TerrainManager", 1);
    qmlRegisterInterface<COPerkManager>("COPerkManager", 1);
    qmlRegisterInterface<MovementPlannerAddIn>("MovementPlannerAddIn", 1);
    qmlRegisterInterface<CampaignMenu>("CampaignMenu", 1);
    qmlRegisterInterface<WikiView>("WikiView", 1);
    qmlRegisterInterface<Mainwindow>("Mainwindow", 1);
    qmlRegisterInterface<VictoryMenue>("VictoryMenue", 1);
    qmlRegisterInterface<CreditsMenue>("CreditsMenue", 1);
    qmlRegisterInterface<Achievementmenu>("Achievementmenu", 1);
    qmlRegisterInterface<OptionMenue>("OptionMenue", 1);
    qmlRegisterInterface<MapSelectionMapsMenue>("MapSelectionMapsMenue", 1);
    qmlRegisterInterface<MapSelectionFilterDialog>("MapSelectionFilterDialog", 1);
    qmlRegisterInterface<MapEditDialog>("MapEditDialog", 1);
    qmlRegisterInterface<CustomCoBoostInfo>("CustomCoBoostInfo", 1);
    qmlRegisterInterface<TerrainFlowData>("TerrainFlowData", 1);
    qmlRegisterInterface<CampaignMapData>("CampaignMapData", 1);
    qmlRegisterInterface<GamepadInfo>("GamepadInfo", 1);
    qmlRegisterInterface<CreatedGui>("CreatedGui", 1);
    qmlRegisterInterface<UiFactory>("UiFactory", 1);
    qmlRegisterInterface<PlayerRecord>("PlayerRecord", 1);
    qmlRegisterInterface<SpecialEvent>("SpecialEvent", 1);
    qmlRegisterInterface<DayToDayRecord>("DayToDayRecord", 1);
    qmlRegisterInterface<MovementPlanner>("MovementPlanner", 1);
    qmlRegisterInterface<GameMenue>("GameMenue", 1);
    qmlRegisterInterface<EditorMenue>("EditorMenue", 1);
    qmlRegisterInterface<BaseGamemenu>("BaseGamemenu", 1);
    qmlRegisterInterface<Basemenu>("Basemenu", 1);
    qmlRegisterInterface<GeneratorMenu>("GeneratorMenu", 1);
    qmlRegisterInterface<PageData>("PageData", 1);

    qmlRegisterInterface<CustomDialog>("CustomDialog", 1);
    qmlRegisterInterface<MainServer>("MainServer", 1);
    qmlRegisterInterface<AutoMatchMaker>("AutoMatchMaker", 1);
    qmlRegisterInterface<Multiplayermenu>("Multiplayermenu", 1);
    qmlRegisterInterface<NetworkGameDataView>("NetworkGameDataView", 1);
#ifdef AUDIOSUPPORT
    qmlRegisterInterface<SoundData>("SoundData", 1);
#endif
    qmlRegisterInterface<AudioManager>("AudioManager", 1);

    // objects
    qmlRegisterInterface<Checkbox>("Checkbox", 1);
    qmlRegisterInterface<ColorSelector>("ColorSelector", 1);
    qmlRegisterInterface<DropDownmenu>("DropDownmenu", 1);
    qmlRegisterInterface<DropDownmenuBase>("DropDownmenuBase", 1);
    qmlRegisterInterface<DropDownmenuColor>("DropDownmenuColor", 1);
    qmlRegisterInterface<DropDownmenuSprite>("DropDownmenuSprite", 1);
    qmlRegisterInterface<FocusableObject>("FocusableObject", 1);
    qmlRegisterInterface<Label>("Label", 1);
    qmlRegisterInterface<Multislider>("Multislider", 1);
    qmlRegisterInterface<Passwordbox>("Passwordbox", 1);
    qmlRegisterInterface<Slider>("Slider", 1);
    qmlRegisterInterface<SpinBox>("SpinBox", 1);
    qmlRegisterInterface<TimeSpinBox>("TimeSpinBox", 1);
    qmlRegisterInterface<TableView>("TableView", 1);
    qmlRegisterInterface<Textbox>("Textbox", 1);
    qmlRegisterInterface<TextInput>("TextInput", 1);
    qmlRegisterInterface<TimeSpinBox>("TimeSpinBox", 1);
    qmlRegisterInterface<Tooltip>("Tooltip", 1);
    qmlRegisterInterface<V_Scrollbar>("V_Scrollbar", 1);
    qmlRegisterInterface<H_Scrollbar>("H_Scrollbar", 1);
}
