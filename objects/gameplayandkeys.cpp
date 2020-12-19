#include "gameplayandkeys.h"

#include "coreengine/mainapp.h"
#include "resource_management/fontmanager.h"

#include "game/gamemap.h"

#include "objects/base/label.h"
#include "objects/base/dropdownmenu.h"
#include "objects/base/slider.h"
#include "objects/base/checkbox.h"
#include "objects/base/spinbox.h"
#include "objects/base/selectkey.h"

GameplayAndKeys::GameplayAndKeys(qint32 heigth)
{
    

    QSize size(Settings::getWidth() - 20,
               heigth);
    m_pOptions = new  Panel(true,  size, size);
    addChild(m_pOptions);

    oxygine::TextStyle style = FontManager::getMainFont24();
    style.color = FontManager::getFontColor();
    style.vAlign = oxygine::TextStyle::VALIGN_DEFAULT;
    style.hAlign = oxygine::TextStyle::HALIGN_LEFT;
    style.multiline = false;

    qint32 y = 10;
    qint32 sliderOffset = 450;

    spLabel pTextfield = new Label(800);
    pTextfield->setStyle(style);
    pTextfield->setHtmlText(tr("Gameplay Settings"));
    pTextfield->setPosition(10, y);
    m_pOptions->addItem(pTextfield);
    y += 40;

    pTextfield = new Label(sliderOffset - 10);
    pTextfield->setStyle(style);
    pTextfield->setHtmlText(tr("Ingame Animations: "));
    pTextfield->setPosition(10, y);
    m_pOptions->addItem(pTextfield);
    QVector<QString> items = {tr("None"), tr("All"), tr("Own"), tr("Ally"), tr("Enemy"),
                             tr("Only Detailed Battle All"), tr("Only Detailed Battle Own"),
                             tr("Only Detailed Battle Ally"), tr("Only Detailed Battle Enemy")};
    spDropDownmenu pAnimationMode = new DropDownmenu(450, items);
    pAnimationMode->setCurrentItem(static_cast<qint32>(Settings::getShowAnimations()));
    pAnimationMode->setPosition(sliderOffset - 130, y);
    pAnimationMode->setTooltipText(tr("Select which ingame animations are played."));
    m_pOptions->addItem(pAnimationMode);
    connect(pAnimationMode.get(), &DropDownmenu::sigItemChanged, [=](qint32 value)
    {
        Settings::setShowAnimations(static_cast<GameEnums::AnimationMode>(value));
    });
    y += 40;

    pTextfield = new Label(sliderOffset - 10);
    pTextfield->setStyle(style);
    pTextfield->setHtmlText(tr("Battle Animations: "));
    pTextfield->setPosition(10, y);
    m_pOptions->addItem(pTextfield);
    items = {tr("Detailed"), tr("Overworld")};
    spDropDownmenu pBattleAnimationMode = new DropDownmenu(450, items);
    pBattleAnimationMode->setTooltipText(tr("Selects which battle animations are played when fighting an enemy."));
    pBattleAnimationMode->setCurrentItem(static_cast<qint32>(Settings::getBattleAnimations()));
    pBattleAnimationMode->setPosition(sliderOffset - 130, y);
    m_pOptions->addItem(pBattleAnimationMode);
    connect(pBattleAnimationMode.get(), &DropDownmenu::sigItemChanged, [=](qint32 value)
    {
        Settings::setBattleAnimations(static_cast<GameEnums::BattleAnimationMode>(value));
    });
    y += 40;

    pTextfield = new Label(sliderOffset - 10);
    pTextfield->setStyle(style);
    pTextfield->setHtmlText(tr("Animation Speed: "));
    pTextfield->setPosition(10, y);
    m_pOptions->addItem(pTextfield);
    spSlider pAnimationSpeed = new Slider(Settings::getWidth() - 20 - sliderOffset, 1, 100, "");
    pAnimationSpeed->setTooltipText(tr("Selects the speed at which animations are played. Except battle and walking animations."));
    pAnimationSpeed->setPosition(sliderOffset - 130, y);
    pAnimationSpeed->setCurrentValue(static_cast<qint32>(Settings::getAnimationSpeedValue()));
    m_pOptions->addItem(pAnimationSpeed);
    connect(pAnimationSpeed.get(), &Slider::sliderValueChanged, [=](qint32 value)
    {
        Settings::setAnimationSpeed(static_cast<quint32>(value));
    });
    y += 40;

    pTextfield = new Label(sliderOffset - 10);
    pTextfield->setStyle(style);
    pTextfield->setHtmlText(tr("Walk Speed: "));
    pTextfield->setPosition(10, y);
    m_pOptions->addItem(pTextfield);
    spSlider pWalkSpeed = new Slider(Settings::getWidth() - 20 - sliderOffset, 1, 100, "");
    pWalkSpeed->setTooltipText(tr("Selects the speed at which units walk across the map."));
    pWalkSpeed->setPosition(sliderOffset - 130, y);
    pWalkSpeed->setCurrentValue(static_cast<qint32>(Settings::getWalkAnimationSpeedValue()));
    m_pOptions->addItem(pWalkSpeed);
    connect(pWalkSpeed.get(), &Slider::sliderValueChanged, [=](qint32 value)
    {
        Settings::setWalkAnimationSpeed(static_cast<quint32>(value));
    });
    y += 40;

    pTextfield = new Label(sliderOffset - 10);
    pTextfield->setStyle(style);
    pTextfield->setHtmlText(tr("Battle Anim. Speed: "));
    pTextfield->setPosition(10, y);
    m_pOptions->addItem(pTextfield);
    spSlider pBattleAnimationSpeed = new Slider(Settings::getWidth() - 20 - sliderOffset, 1, 100, "");
    pBattleAnimationSpeed->setTooltipText(tr("Selects the speed at which battle animations are played."));
    pBattleAnimationSpeed->setPosition(sliderOffset - 130, y);
    pBattleAnimationSpeed->setCurrentValue(static_cast<qint32>(Settings::getBattleAnimationSpeedValue()));
    m_pOptions->addItem(pBattleAnimationSpeed);
    connect(pBattleAnimationSpeed.get(), &Slider::sliderValueChanged, [=](qint32 value)
    {
        Settings::setBattleAnimationSpeed(static_cast<quint32>(value));
    });
    y += 40;

    pTextfield = new Label(sliderOffset - 10);
    pTextfield->setStyle(style);
    pTextfield->setHtmlText(tr("Dialog Speed: "));
    pTextfield->setPosition(10, y);
    m_pOptions->addItem(pTextfield);
    spSlider pDialogAnimationSpeed = new Slider(Settings::getWidth() - 20 - sliderOffset, 1, 100, "");
    pDialogAnimationSpeed->setTooltipText(tr("Selects the speed at which dialog animations are played."));
    pDialogAnimationSpeed->setPosition(sliderOffset - 130, y);
    pDialogAnimationSpeed->setCurrentValue(static_cast<qint32>(Settings::getDialogAnimationSpeedValue()));
    m_pOptions->addItem(pDialogAnimationSpeed);
    connect(pDialogAnimationSpeed.get(), &Slider::sliderValueChanged, [=](qint32 value)
    {
        Settings::setDialogAnimationSpeed(static_cast<quint32>(value));
    });
    y += 40;

    pTextfield = new Label(sliderOffset - 10);
    pTextfield->setStyle(style);
    pTextfield->setHtmlText(tr("Multi Turn Plantime: "));
    pTextfield->setPosition(10, y);
    m_pOptions->addItem(pTextfield);
    spSlider pMultiTurnCounter = new Slider(Settings::getWidth() - 20 - sliderOffset, 1, 10, "");
    pMultiTurnCounter->setTooltipText(tr("Selects the amount of turns you can preplan with a unit."));
    pMultiTurnCounter->setPosition(sliderOffset - 130, y);
    pMultiTurnCounter->setCurrentValue(static_cast<qint32>(Settings::getMultiTurnCounter()));
    m_pOptions->addItem(pMultiTurnCounter);
    connect(pMultiTurnCounter.get(), &Slider::sliderValueChanged, [=](qint32 value)
    {
        Settings::setMultiTurnCounter(static_cast<quint32>(value));
    });
    y += 40;

    pTextfield = new Label(sliderOffset - 10);
    pTextfield->setStyle(style);
    pTextfield->setHtmlText(tr("Auto End Turn: "));
    pTextfield->setPosition(10, y);
    m_pOptions->addItem(pTextfield);
    spCheckbox pCheckbox = new Checkbox();
    pCheckbox->setTooltipText(tr("If active the game will automatically end your turn if you can't give any orders anymore."));
    pCheckbox->setChecked(Settings::getAutoEndTurn());
    connect(pCheckbox.get(), &Checkbox::checkChanged, [=](bool value)
    {
        Settings::setAutoEndTurn(value);
    });
    pCheckbox->setPosition(sliderOffset - 130, y);
    m_pOptions->addItem(pCheckbox);
    y += 40;

    pTextfield = new Label(sliderOffset - 10);
    pTextfield->setStyle(style);
    pTextfield->setHtmlText(tr("Menu Heigth: "));
    pTextfield->setPosition(10, y);
    m_pOptions->addItem(pTextfield);
    spSlider pMenuItemHeigth = new Slider(Settings::getWidth() - 20 - sliderOffset, 10, (Settings::getHeight() - GameMap::getImageSize() * 2) / GameMap::getImageSize(), "");
    pMenuItemHeigth->setTooltipText(tr("Amount of items per row for ingame menus before a new row is added."));
    pMenuItemHeigth->setPosition(sliderOffset - 130, y);
    pMenuItemHeigth->setCurrentValue(static_cast<qint32>(Settings::getMenuItemCount()));
    m_pOptions->addItem(pMenuItemHeigth);
    connect(pMenuItemHeigth.get(), &Slider::sliderValueChanged, [=](qint32 value)
    {
        Settings::setMenuItemCount(static_cast<quint32>(value));
    });
    y += 40;

    pTextfield = new Label(sliderOffset - 10);
    pTextfield->setStyle(style);
    pTextfield->setHtmlText(tr("Shown Players: "));
    pTextfield->setPosition(10, y);
    m_pOptions->addItem(pTextfield);
    spSpinBox showCoCount = new SpinBox(200, 0, std::numeric_limits<qint32>::max());
    showCoCount->setInfinityValue(0);
    showCoCount->setTooltipText(tr("Selects the amount of players shown in game on the sidebar."));
    showCoCount->setCurrentValue(Settings::getShowCoCount());
    showCoCount->setPosition(sliderOffset - 130, y);
    connect(showCoCount.get(), &SpinBox::sigValueChanged, Settings::getInstance(), &Settings::setShowCoCount);
    m_pOptions->addItem(showCoCount);
    y += 40;

    pTextfield = new Label(sliderOffset - 10);
    pTextfield->setStyle(style);
    pTextfield->setHtmlText(tr("Show PC Cursor: "));
    pTextfield->setPosition(10, y);
    m_pOptions->addItem(pTextfield);
    pCheckbox = new Checkbox();
    pCheckbox->setTooltipText(tr("If active the windows cursors is hidden during a game. Giving you a more Gameboy like feeling."));
    pCheckbox->setChecked(Settings::getShowCursor());
    connect(pCheckbox.get(), &Checkbox::checkChanged, [=](bool value)
    {
        Settings::setShowCursor(value);
    });
    pCheckbox->setPosition(sliderOffset - 130, y);
    m_pOptions->addItem(pCheckbox);
    y += 40;

    pTextfield = new Label(sliderOffset - 10);
    pTextfield->setStyle(style);
    pTextfield->setHtmlText(tr("Animated Markers: "));
    pTextfield->setPosition(10, y);
    m_pOptions->addItem(pTextfield);
    pCheckbox = new Checkbox();
    pCheckbox->setTooltipText(tr("If active the currently selectable fiedls get animated."));
    pCheckbox->setChecked(!Settings::getStaticMarkedFields());
    connect(pCheckbox.get(), &Checkbox::checkChanged, [=](bool value)
    {
        Settings::setStaticMarkedFields(!value);
    });
    pCheckbox->setPosition(sliderOffset - 130, y);
    m_pOptions->addItem(pCheckbox);
    y += 40;

    pTextfield = new Label(sliderOffset - 10);
    pTextfield->setStyle(style);
    pTextfield->setHtmlText(tr("CO Info Position: "));
    pTextfield->setPosition(10, y);
    m_pOptions->addItem(pTextfield);
    items = {tr("Flipping"), tr("Left"), tr("Right")};
    spDropDownmenu pCoInfOMode = new DropDownmenu(450, items);
    pCoInfOMode->setCurrentItem(static_cast<qint32>(Settings::getCoInfoPosition()));
    pCoInfOMode->setPosition(sliderOffset - 130, y);
    pCoInfOMode->setTooltipText(tr("Select where the CO Info is shown. Where Flipping positions it at the opposite side of the cursor."));
    m_pOptions->addItem(pCoInfOMode);
    connect(pCoInfOMode.get(), &DropDownmenu::sigItemChanged, [=](qint32 value)
    {
        Settings::setCoInfoPosition(static_cast<GameEnums::COInfoPosition>(value));
    });
    y += 40;

    pTextfield = new Label(sliderOffset - 10);
    pTextfield->setStyle(style);
    pTextfield->setHtmlText(tr("Auto Scrolling: "));
    pTextfield->setPosition(10, y);
    m_pOptions->addItem(pTextfield);
    pCheckbox = new Checkbox();
    pCheckbox->setTooltipText(tr("If active the map is scrolled automatically while the cursor is at the screen borders."));
    pCheckbox->setChecked(Settings::getAutoScrolling());
    connect(pCheckbox.get(), &Checkbox::checkChanged, [=](bool value)
    {
        Settings::setAutoScrolling(value);
    });
    pCheckbox->setPosition(sliderOffset - 130, y);
    m_pOptions->addItem(pCheckbox);
    y += 40;

    pTextfield = new Label(sliderOffset - 10);
    pTextfield->setStyle(style);
    pTextfield->setHtmlText(tr("Show Coordinates: "));
    pTextfield->setPosition(10, y);
    m_pOptions->addItem(pTextfield);
    pCheckbox = new Checkbox();
    pCheckbox->setTooltipText(tr("If active the map coordinates are shown during a game."));
    pCheckbox->setChecked(Settings::getShowIngameCoordinates());
    connect(pCheckbox.get(), &Checkbox::checkChanged, [=](bool value)
    {
        Settings::setShowIngameCoordinates(value);
    });
    pCheckbox->setPosition(sliderOffset - 130, y);
    m_pOptions->addItem(pCheckbox);
    y += 40;

    pTextfield = new Label(sliderOffset - 10);
    pTextfield->setStyle(style);
    pTextfield->setHtmlText(tr("Auto Camera: "));
    pTextfield->setPosition(10, y);
    m_pOptions->addItem(pTextfield);
    pCheckbox = new Checkbox();
    pCheckbox->setTooltipText(tr("If active the map is centered on the unit action during other player turns. If the field is visible to the player."));
    pCheckbox->setChecked(Settings::getAutoCamera());
    connect(pCheckbox.get(), &Checkbox::checkChanged, [=](bool value)
    {
        Settings::setAutoCamera(value);
    });
    pCheckbox->setPosition(sliderOffset - 130, y);
    m_pOptions->addItem(pCheckbox);
    y += 40;

    pTextfield = new Label(sliderOffset - 10);
    pTextfield->setStyle(style);
    pTextfield->setHtmlText(tr("Auto Camare Mode: "));
    pTextfield->setPosition(10, y);
    m_pOptions->addItem(pTextfield);
    items = {tr("Last Position"), tr("Owned HQ")};
    spDropDownmenu pAutoFocusMode = new DropDownmenu(450, items);
    pAutoFocusMode->setCurrentItem(static_cast<qint32>(Settings::getAutoFocusing()));
    pAutoFocusMode->setPosition(sliderOffset - 130, y);
    pAutoFocusMode->setTooltipText(tr("Select where the game starts during a human player phase, when auto focusing is active."));
    m_pOptions->addItem(pAutoFocusMode);
    connect(pAutoFocusMode.get(), &DropDownmenu::sigItemChanged, [=](qint32 value)
    {
        Settings::setAutoFocusing(static_cast<GameEnums::AutoFocusing>(value));
    });
    y += 40;

    pTextfield = new Label(sliderOffset - 10);
    pTextfield->setStyle(style);
    pTextfield->setHtmlText(tr("Ingame Keys"));
    pTextfield->setPosition(10, y);
    m_pOptions->addItem(pTextfield);
    y += 40;

    pTextfield = new Label(sliderOffset - 10);
    pTextfield->setStyle(style);
    pTextfield->setHtmlText(tr("Key Up: "));
    pTextfield->setPosition(10, y);
    m_pOptions->addItem(pTextfield);
    spSelectKey pSelectKey = new SelectKey(Settings::getKey_up());
    pSelectKey->setTooltipText(tr("Key for moving the cursor up."));
    pSelectKey->setPosition(sliderOffset - 130, y);
    connect(pSelectKey.get(), &SelectKey::sigKeyChanged, Settings::getInstance(), &Settings::setKey_up, Qt::QueuedConnection);
    m_pOptions->addItem(pSelectKey);
    pSelectKey = new SelectKey(Settings::getKey_up2());
    pSelectKey->setTooltipText(tr("Key for moving the cursor up."));
    pSelectKey->setPosition(sliderOffset + 70, y);
    connect(pSelectKey.get(), &SelectKey::sigKeyChanged, Settings::getInstance(), &Settings::setKey_up2, Qt::QueuedConnection);
    m_pOptions->addItem(pSelectKey);
    y += 40;

    pTextfield = new Label(sliderOffset - 10);
    pTextfield->setStyle(style);
    pTextfield->setHtmlText(tr("Key Left: "));
    pTextfield->setPosition(10, y);
    m_pOptions->addItem(pTextfield);
    pSelectKey = new SelectKey(Settings::getKey_left());
    pSelectKey->setTooltipText(tr("Key for moving the cursor left."));
    pSelectKey->setPosition(sliderOffset - 130, y);
    connect(pSelectKey.get(), &SelectKey::sigKeyChanged, Settings::getInstance(), &Settings::setKey_left, Qt::QueuedConnection);
    m_pOptions->addItem(pSelectKey);
    pSelectKey = new SelectKey(Settings::getKey_left2());
    pSelectKey->setTooltipText(tr("Key for moving the cursor left."));
    pSelectKey->setPosition(sliderOffset + 70, y);
    connect(pSelectKey.get(), &SelectKey::sigKeyChanged, Settings::getInstance(), &Settings::setKey_left2, Qt::QueuedConnection);
    m_pOptions->addItem(pSelectKey);
    y += 40;

    pTextfield = new Label(sliderOffset - 10);
    pTextfield->setStyle(style);
    pTextfield->setHtmlText(tr("Key Down: "));
    pTextfield->setPosition(10, y);
    m_pOptions->addItem(pTextfield);
    pSelectKey = new SelectKey(Settings::getKey_down());
    pSelectKey->setTooltipText(tr("Key for moving the cursor down."));
    pSelectKey->setPosition(sliderOffset - 130, y);
    connect(pSelectKey.get(), &SelectKey::sigKeyChanged, Settings::getInstance(), &Settings::setKey_down, Qt::QueuedConnection);
    m_pOptions->addItem(pSelectKey);
    pSelectKey = new SelectKey(Settings::getKey_down2());
    pSelectKey->setTooltipText(tr("Key for moving the cursor down."));
    pSelectKey->setPosition(sliderOffset + 70, y);
    connect(pSelectKey.get(), &SelectKey::sigKeyChanged, Settings::getInstance(), &Settings::setKey_down2, Qt::QueuedConnection);
    m_pOptions->addItem(pSelectKey);
    y += 40;

    pTextfield = new Label(sliderOffset - 10);
    pTextfield->setStyle(style);
    pTextfield->setHtmlText(tr("Key Right: "));
    pTextfield->setPosition(10, y);
    m_pOptions->addItem(pTextfield);
    pSelectKey = new SelectKey(Settings::getKey_right());
    pSelectKey->setTooltipText(tr("Key for moving the cursor right."));
    pSelectKey->setPosition(sliderOffset - 130, y);
    connect(pSelectKey.get(), &SelectKey::sigKeyChanged, Settings::getInstance(), &Settings::setKey_right, Qt::QueuedConnection);
    m_pOptions->addItem(pSelectKey);
    pSelectKey = new SelectKey(Settings::getKey_right2());
    pSelectKey->setTooltipText(tr("Key for moving the cursor right."));
    pSelectKey->setPosition(sliderOffset + 70, y);
    connect(pSelectKey.get(), &SelectKey::sigKeyChanged, Settings::getInstance(), &Settings::setKey_right2, Qt::QueuedConnection);
    m_pOptions->addItem(pSelectKey);
    y += 40;

    pTextfield = new Label(sliderOffset - 10);
    pTextfield->setStyle(style);
    pTextfield->setHtmlText(tr("Key Confirm: "));
    pTextfield->setPosition(10, y);
    m_pOptions->addItem(pTextfield);
    pSelectKey = new SelectKey(Settings::getKey_confirm());
    pSelectKey->setTooltipText(tr("Key for confirming any action or input in the game."));
    pSelectKey->setPosition(sliderOffset - 130, y);
    connect(pSelectKey.get(), &SelectKey::sigKeyChanged, Settings::getInstance(), &Settings::setKey_confirm, Qt::QueuedConnection);
    m_pOptions->addItem(pSelectKey);
    pSelectKey = new SelectKey(Settings::getKey_confirm2());
    pSelectKey->setTooltipText(tr("Key for confirming any action or input in the game."));
    pSelectKey->setPosition(sliderOffset + 70, y);
    connect(pSelectKey.get(), &SelectKey::sigKeyChanged, Settings::getInstance(), &Settings::setKey_confirm2, Qt::QueuedConnection);
    m_pOptions->addItem(pSelectKey);
    y += 40;

    pTextfield = new Label(sliderOffset - 10);
    pTextfield->setStyle(style);
    pTextfield->setHtmlText(tr("Key Cancel: "));
    pTextfield->setPosition(10, y);
    m_pOptions->addItem(pTextfield);
    pSelectKey = new SelectKey(Settings::getKey_cancel());
    pSelectKey->setTooltipText(tr("Key for canceling any action or input in the game."));
    pSelectKey->setPosition(sliderOffset - 130, y);
    connect(pSelectKey.get(), &SelectKey::sigKeyChanged, Settings::getInstance(), &Settings::setKey_cancel, Qt::QueuedConnection);
    m_pOptions->addItem(pSelectKey);
    pSelectKey = new SelectKey(Settings::getKey_cancel2());
    pSelectKey->setTooltipText(tr("Key for canceling any action or input in the game."));
    pSelectKey->setPosition(sliderOffset + 70, y);
    connect(pSelectKey.get(), &SelectKey::sigKeyChanged, Settings::getInstance(), &Settings::setKey_cancel2, Qt::QueuedConnection);
    m_pOptions->addItem(pSelectKey);
    y += 40;

    pTextfield = new Label(sliderOffset - 10);
    pTextfield->setStyle(style);
    pTextfield->setHtmlText(tr("Key Next: "));
    pTextfield->setPosition(10, y);
    m_pOptions->addItem(pTextfield);
    pSelectKey = new SelectKey(Settings::getKey_next());
    pSelectKey->setTooltipText(tr("Key for moving the cursor to the next possible field unit etc."));
    pSelectKey->setPosition(sliderOffset - 130, y);
    connect(pSelectKey.get(), &SelectKey::sigKeyChanged, Settings::getInstance(), &Settings::setKey_next, Qt::QueuedConnection);
    m_pOptions->addItem(pSelectKey);
    pSelectKey = new SelectKey(Settings::getKey_next2());
    pSelectKey->setTooltipText(tr("Key for moving the cursor to the next possible field unit etc."));
    pSelectKey->setPosition(sliderOffset + 70, y);
    connect(pSelectKey.get(), &SelectKey::sigKeyChanged, Settings::getInstance(), &Settings::setKey_next2, Qt::QueuedConnection);
    m_pOptions->addItem(pSelectKey);
    y += 40;

    pTextfield = new Label(sliderOffset - 10);
    pTextfield->setStyle(style);
    pTextfield->setHtmlText(tr("Key Previous: "));
    pTextfield->setPosition(10, y);
    m_pOptions->addItem(pTextfield);
    pSelectKey = new SelectKey(Settings::getKey_previous());
    pSelectKey->setTooltipText(tr("Key for moving the cursor to the previous possible field unit etc."));
    pSelectKey->setPosition(sliderOffset - 130, y);
    connect(pSelectKey.get(), &SelectKey::sigKeyChanged, Settings::getInstance(), &Settings::setKey_previous, Qt::QueuedConnection);
    m_pOptions->addItem(pSelectKey);
    pSelectKey = new SelectKey(Settings::getKey_previous2());
    pSelectKey->setTooltipText(tr("Key for moving the cursor to the previous possible field unit etc."));
    pSelectKey->setPosition(sliderOffset + 70, y);
    connect(pSelectKey.get(), &SelectKey::sigKeyChanged, Settings::getInstance(), &Settings::setKey_previous2, Qt::QueuedConnection);
    m_pOptions->addItem(pSelectKey);
    y += 40;

    pTextfield = new Label(sliderOffset - 10);
    pTextfield->setStyle(style);
    pTextfield->setHtmlText(tr("Key Quicksave 1: "));
    m_pOptions->addItem(pTextfield);
    pTextfield->setPosition(10, y);
    pSelectKey = new SelectKey(Settings::getKey_quicksave1());
    pSelectKey->setTooltipText(tr("Key for quick saving slot 1."));
    pSelectKey->setPosition(sliderOffset - 130, y);
    connect(pSelectKey.get(), &SelectKey::sigKeyChanged, Settings::getInstance(), &Settings::setKey_quicksave1, Qt::QueuedConnection);
    m_pOptions->addItem(pSelectKey);
    y += 40;

    pTextfield = new Label(sliderOffset - 10);
    pTextfield->setStyle(style);
    pTextfield->setHtmlText(tr("Key Quickload 1: "));
    m_pOptions->addItem(pTextfield);
    pTextfield->setPosition(10, y);
    pSelectKey = new SelectKey(Settings::getKey_quickload1());
    pSelectKey->setTooltipText(tr("Key for quick loading slot 1."));
    pSelectKey->setPosition(sliderOffset - 130, y);
    connect(pSelectKey.get(), &SelectKey::sigKeyChanged, Settings::getInstance(), &Settings::setKey_quickload1, Qt::QueuedConnection);
    m_pOptions->addItem(pSelectKey);
    y += 40;

    pTextfield = new Label(sliderOffset - 10);
    pTextfield->setStyle(style);
    pTextfield->setHtmlText(tr("Key Quicksave 2: "));
    m_pOptions->addItem(pTextfield);
    pTextfield->setPosition(10, y);
    pSelectKey = new SelectKey(Settings::getKey_quicksave2());
    pSelectKey->setTooltipText(tr("Key for quick saving slot 2."));
    pSelectKey->setPosition(sliderOffset - 130, y);
    connect(pSelectKey.get(), &SelectKey::sigKeyChanged, Settings::getInstance(), &Settings::setKey_quicksave2, Qt::QueuedConnection);
    m_pOptions->addItem(pSelectKey);
    y += 40;

    pTextfield = new Label(sliderOffset - 10);
    pTextfield->setStyle(style);
    pTextfield->setHtmlText(tr("Key Quickload 2: "));
    m_pOptions->addItem(pTextfield);
    pTextfield->setPosition(10, y);
    pSelectKey = new SelectKey(Settings::getKey_quickload2());
    pSelectKey->setTooltipText(tr("Key for quick loading slot 2."));
    pSelectKey->setPosition(sliderOffset - 130, y);
    connect(pSelectKey.get(), &SelectKey::sigKeyChanged, Settings::getInstance(), &Settings::setKey_quickload2, Qt::QueuedConnection);
    m_pOptions->addItem(pSelectKey);
    y += 40;

    pTextfield = new Label(sliderOffset - 10);
    pTextfield->setStyle(style);
    pTextfield->setHtmlText(tr("Key Information: "));
    m_pOptions->addItem(pTextfield);
    pTextfield->setPosition(10, y);
    pSelectKey = new SelectKey(Settings::getKey_information());
    pSelectKey->setTooltipText(tr("Key to show information about the current field, action, unit at any time in the game."));
    pSelectKey->setPosition(sliderOffset - 130, y);
    connect(pSelectKey.get(), &SelectKey::sigKeyChanged, Settings::getInstance(), &Settings::setKey_information, Qt::QueuedConnection);
    m_pOptions->addItem(pSelectKey);
    pSelectKey = new SelectKey(Settings::getKey_information2());
    pSelectKey->setTooltipText(tr("Key to show information about the current field, action, unit at any time in the game."));
    pSelectKey->setPosition(sliderOffset + 70, y);
    connect(pSelectKey.get(), &SelectKey::sigKeyChanged, Settings::getInstance(), &Settings::setKey_information2, Qt::QueuedConnection);
    m_pOptions->addItem(pSelectKey);
    y += 40;

    pTextfield = new Label(sliderOffset - 10);
    pTextfield->setStyle(style);
    pTextfield->setHtmlText(tr("Key Move Map Up: "));
    m_pOptions->addItem(pTextfield);
    pTextfield->setPosition(10, y);
    pSelectKey = new SelectKey(Settings::getKey_moveMapUp());
    pSelectKey->setTooltipText(tr("Key to move the map a field up."));
    pSelectKey->setPosition(sliderOffset - 130, y);
    connect(pSelectKey.get(), &SelectKey::sigKeyChanged, Settings::getInstance(), &Settings::setKey_moveMapUp, Qt::QueuedConnection);
    m_pOptions->addItem(pSelectKey);
    pSelectKey = new SelectKey(Settings::getKey_moveMapUp2());
    pSelectKey->setTooltipText(tr("Key to move the map a field up."));
    pSelectKey->setPosition(sliderOffset + 70, y);
    connect(pSelectKey.get(), &SelectKey::sigKeyChanged, Settings::getInstance(), &Settings::setKey_moveMapUp2, Qt::QueuedConnection);
    m_pOptions->addItem(pSelectKey);
    y += 40;

    pTextfield = new Label(sliderOffset - 10);
    pTextfield->setStyle(style);
    pTextfield->setHtmlText(tr("Key Move Map Left: "));
    m_pOptions->addItem(pTextfield);
    pTextfield->setPosition(10, y);
    pSelectKey = new SelectKey(Settings::getKey_moveMapLeft());
    pSelectKey->setTooltipText(tr("Key to move the map a field left."));
    pSelectKey->setPosition(sliderOffset - 130, y);
    connect(pSelectKey.get(), &SelectKey::sigKeyChanged, Settings::getInstance(), &Settings::setKey_moveMapLeft, Qt::QueuedConnection);
    m_pOptions->addItem(pSelectKey);
    pSelectKey = new SelectKey(Settings::getKey_moveMapLeft2());
    pSelectKey->setTooltipText(tr("Key to move the map a field left."));
    pSelectKey->setPosition(sliderOffset + 70, y);
    connect(pSelectKey.get(), &SelectKey::sigKeyChanged, Settings::getInstance(), &Settings::setKey_moveMapLeft2, Qt::QueuedConnection);
    m_pOptions->addItem(pSelectKey);
    y += 40;

    pTextfield = new Label(sliderOffset - 10);
    pTextfield->setStyle(style);
    pTextfield->setHtmlText(tr("Key Move Map Down: "));
    m_pOptions->addItem(pTextfield);
    pTextfield->setPosition(10, y);
    pSelectKey = new SelectKey(Settings::getKey_moveMapDown());
    pSelectKey->setTooltipText(tr("Key to move the map a field down."));
    pSelectKey->setPosition(sliderOffset - 130, y);
    connect(pSelectKey.get(), &SelectKey::sigKeyChanged, Settings::getInstance(), &Settings::setKey_moveMapDown, Qt::QueuedConnection);
    m_pOptions->addItem(pSelectKey);
    pSelectKey = new SelectKey(Settings::getKey_moveMapDown2());
    pSelectKey->setTooltipText(tr("Key to move the map a field down."));
    pSelectKey->setPosition(sliderOffset + 70, y);
    connect(pSelectKey.get(), &SelectKey::sigKeyChanged, Settings::getInstance(), &Settings::setKey_moveMapDown2, Qt::QueuedConnection);
    m_pOptions->addItem(pSelectKey);
    y += 40;

    pTextfield = new Label(sliderOffset - 10);
    pTextfield->setStyle(style);
    pTextfield->setHtmlText(tr("Key Move Map Right: "));
    m_pOptions->addItem(pTextfield);
    pTextfield->setPosition(10, y);
    pSelectKey = new SelectKey(Settings::getKey_moveMapRight());
    pSelectKey->setTooltipText(tr("Key to move the map a field right."));
    pSelectKey->setPosition(sliderOffset - 130, y);
    connect(pSelectKey.get(), &SelectKey::sigKeyChanged, Settings::getInstance(), &Settings::setKey_moveMapRight, Qt::QueuedConnection);
    m_pOptions->addItem(pSelectKey);
    pSelectKey = new SelectKey(Settings::getKey_moveMapRight2());
    pSelectKey->setTooltipText(tr("Key to move the map a field right."));
    pSelectKey->setPosition(sliderOffset + 70, y);
    connect(pSelectKey.get(), &SelectKey::sigKeyChanged, Settings::getInstance(), &Settings::setKey_moveMapRight2, Qt::QueuedConnection);
    m_pOptions->addItem(pSelectKey);
    y += 40;

    pTextfield = new Label(sliderOffset - 10);
    pTextfield->setStyle(style);
    pTextfield->setHtmlText(tr("Key Zoom In: "));
    m_pOptions->addItem(pTextfield);
    pTextfield->setPosition(10, y);
    pSelectKey = new SelectKey(Settings::getKey_MapZoomIn());
    pSelectKey->setTooltipText(tr("Key to zoom into the map."));
    pSelectKey->setPosition(sliderOffset - 130, y);
    connect(pSelectKey.get(), &SelectKey::sigKeyChanged, Settings::getInstance(), &Settings::setKey_MapZoomIn, Qt::QueuedConnection);
    m_pOptions->addItem(pSelectKey);
    pSelectKey = new SelectKey(Settings::getKey_MapZoomIn2());
    pSelectKey->setTooltipText(tr("Key to zoom into the map."));
    pSelectKey->setPosition(sliderOffset + 70, y);
    connect(pSelectKey.get(), &SelectKey::sigKeyChanged, Settings::getInstance(), &Settings::setKey_MapZoomIn2, Qt::QueuedConnection);
    m_pOptions->addItem(pSelectKey);
    y += 40;

    pTextfield = new Label(sliderOffset - 10);
    pTextfield->setStyle(style);
    pTextfield->setHtmlText(tr("Key Zoom Out: "));
    m_pOptions->addItem(pTextfield);
    pTextfield->setPosition(10, y);
    pSelectKey = new SelectKey(Settings::getKey_MapZoomOut());
    pSelectKey->setTooltipText(tr("Key to zoom out of the map."));
    pSelectKey->setPosition(sliderOffset - 130, y);
    connect(pSelectKey.get(), &SelectKey::sigKeyChanged, Settings::getInstance(), &Settings::setKey_MapZoomOut, Qt::QueuedConnection);
    m_pOptions->addItem(pSelectKey);
    pSelectKey = new SelectKey(Settings::getKey_MapZoomOut2());
    pSelectKey->setTooltipText(tr("Key to zoom out of the map."));
    pSelectKey->setPosition(sliderOffset + 70, y);
    connect(pSelectKey.get(), &SelectKey::sigKeyChanged, Settings::getInstance(), &Settings::setKey_MapZoomOut2, Qt::QueuedConnection);
    m_pOptions->addItem(pSelectKey);
    y += 40;

    pTextfield = new Label(sliderOffset - 10);
    pTextfield->setStyle(style);
    pTextfield->setHtmlText(tr("Key Show Indirects: "));
    m_pOptions->addItem(pTextfield);
    pTextfield->setPosition(10, y);
    pSelectKey = new SelectKey(Settings::getKey_ShowIndirectAttackFields());
    pSelectKey->setTooltipText(tr("Key to show where all enemy indirect units can attack near the selected unit."));
    pSelectKey->setPosition(sliderOffset - 130, y);
    connect(pSelectKey.get(), &SelectKey::sigKeyChanged, Settings::getInstance(), &Settings::setKey_ShowIndirectAttackFields, Qt::QueuedConnection);
    m_pOptions->addItem(pSelectKey);
    pSelectKey = new SelectKey(Settings::getKey_ShowIndirectAttackFields2());
    pSelectKey->setTooltipText(tr("Key to show where all enemy indirect units can attack near the selected unit."));
    pSelectKey->setPosition(sliderOffset + 70, y);
    connect(pSelectKey.get(), &SelectKey::sigKeyChanged, Settings::getInstance(), &Settings::setKey_ShowIndirectAttackFields2, Qt::QueuedConnection);
    m_pOptions->addItem(pSelectKey);
    y += 40;

    pTextfield = new Label(sliderOffset - 10);
    pTextfield->setStyle(style);
    pTextfield->setHtmlText(tr("Key Show all: "));
    m_pOptions->addItem(pTextfield);
    pTextfield->setPosition(10, y);
    pSelectKey = new SelectKey(Settings::getKey_ShowAttackFields());
    pSelectKey->setTooltipText(tr("Key to show where all enemy units can attack near the selected unit."));
    pSelectKey->setPosition(sliderOffset - 130, y);
    connect(pSelectKey.get(), &SelectKey::sigKeyChanged, Settings::getInstance(), &Settings::setKey_ShowAttackFields, Qt::QueuedConnection);
    m_pOptions->addItem(pSelectKey);
    pSelectKey = new SelectKey(Settings::getKey_ShowAttackFields2());
    pSelectKey->setTooltipText(tr("Key to show where all enemy units can attack near the selected unit."));
    pSelectKey->setPosition(sliderOffset + 70, y);
    connect(pSelectKey.get(), &SelectKey::sigKeyChanged, Settings::getInstance(), &Settings::setKey_ShowAttackFields2, Qt::QueuedConnection);
    m_pOptions->addItem(pSelectKey);
    y += 40;

    pTextfield = new Label(sliderOffset - 10);
    pTextfield->setStyle(style);
    pTextfield->setHtmlText(tr("Key Editor"));
    m_pOptions->addItem(pTextfield);
    pTextfield->setPosition(10, y);

    pTextfield = new Label(sliderOffset - 10);
    pTextfield->setStyle(style);
    pTextfield->setHtmlText(tr("Key Place Terrain: "));
    m_pOptions->addItem(pTextfield);
    pTextfield->setPosition(10, y);
    pSelectKey = new SelectKey(Settings::getKey_EditorPlaceTerrain());
    pSelectKey->setTooltipText(tr("Key to select Place Terrain in the editor"));
    pSelectKey->setPosition(sliderOffset - 130, y);
    connect(pSelectKey.get(), &SelectKey::sigKeyChanged, Settings::getInstance(), &Settings::setKey_EditorPlaceTerrain, Qt::QueuedConnection);
    m_pOptions->addItem(pSelectKey);
    y += 40;

    pTextfield = new Label(sliderOffset - 10);
    pTextfield->setStyle(style);
    pTextfield->setHtmlText(tr("Key Place Unit: "));
    m_pOptions->addItem(pTextfield);
    pTextfield->setPosition(10, y);
    pSelectKey = new SelectKey(Settings::getKey_EditorPlaceUnit());
    pSelectKey->setTooltipText(tr("Key to select Place Unit in the editor"));
    pSelectKey->setPosition(sliderOffset - 130, y);
    connect(pSelectKey.get(), &SelectKey::sigKeyChanged, Settings::getInstance(), &Settings::setKey_EditorPlaceUnit, Qt::QueuedConnection);
    m_pOptions->addItem(pSelectKey);
    y += 40;

    pTextfield = new Label(sliderOffset - 10);
    pTextfield->setStyle(style);
    pTextfield->setHtmlText(tr("Key Place Building: "));
    m_pOptions->addItem(pTextfield);
    pTextfield->setPosition(10, y);
    pSelectKey = new SelectKey(Settings::getKey_EditorPlaceBuilding());
    pSelectKey->setTooltipText(tr("Key to select Place Building in the editor"));
    pSelectKey->setPosition(sliderOffset - 130, y);
    connect(pSelectKey.get(), &SelectKey::sigKeyChanged, Settings::getInstance(), &Settings::setKey_EditorPlaceBuilding, Qt::QueuedConnection);
    m_pOptions->addItem(pSelectKey);
    y += 40;

    pTextfield = new Label(sliderOffset - 10);
    pTextfield->setStyle(style);
    pTextfield->setHtmlText(tr("Key Next Team: "));
    m_pOptions->addItem(pTextfield);
    pTextfield->setPosition(10, y);
    pSelectKey = new SelectKey(Settings::getKey_EditorNextTeam());
    pSelectKey->setTooltipText(tr("Key to select the next player in the editor"));
    pSelectKey->setPosition(sliderOffset - 130, y);
    connect(pSelectKey.get(), &SelectKey::sigKeyChanged, Settings::getInstance(), &Settings::setKey_EditorNextTeam, Qt::QueuedConnection);
    m_pOptions->addItem(pSelectKey);
    y += 40;

    pTextfield = new Label(sliderOffset - 10);
    pTextfield->setStyle(style);
    pTextfield->setHtmlText(tr("Key Previous Team: "));
    m_pOptions->addItem(pTextfield);
    pTextfield->setPosition(10, y);
    pSelectKey = new SelectKey(Settings::getKey_EditorPreviousTeam());
    pSelectKey->setTooltipText(tr("Key to select the previous player in the editor"));
    pSelectKey->setPosition(sliderOffset - 130, y);
    connect(pSelectKey.get(), &SelectKey::sigKeyChanged, Settings::getInstance(), &Settings::setKey_EditorPreviousTeam, Qt::QueuedConnection);
    m_pOptions->addItem(pSelectKey);
    y += 40;

    pTextfield = new Label(sliderOffset - 10);
    pTextfield->setStyle(style);
    pTextfield->setHtmlText(tr("Key Next Item: "));
    m_pOptions->addItem(pTextfield);
    pTextfield->setPosition(10, y);
    pSelectKey = new SelectKey(Settings::getKey_EditorSelectionRight());
    pSelectKey->setTooltipText(tr("Key to select the next editor item"));
    pSelectKey->setPosition(sliderOffset - 130, y);
    connect(pSelectKey.get(), &SelectKey::sigKeyChanged, Settings::getInstance(), &Settings::setKey_EditorSelectionRight, Qt::QueuedConnection);
    m_pOptions->addItem(pSelectKey);
    y += 40;

    pTextfield = new Label(sliderOffset - 10);
    pTextfield->setStyle(style);
    pTextfield->setHtmlText(tr("Key Previous Item: "));
    m_pOptions->addItem(pTextfield);
    pTextfield->setPosition(10, y);
    pSelectKey = new SelectKey(Settings::getKey_EditorSelectionLeft());
    pSelectKey->setTooltipText(tr("Key to select the previous editor item"));
    pSelectKey->setPosition(sliderOffset - 130, y);
    connect(pSelectKey.get(), &SelectKey::sigKeyChanged, Settings::getInstance(), &Settings::setKey_EditorSelectionLeft, Qt::QueuedConnection);
    m_pOptions->addItem(pSelectKey);
    y += 40;

    pTextfield = new Label(sliderOffset - 10);
    pTextfield->setStyle(style);
    pTextfield->setHtmlText(tr("Screenshot: "));
    pTextfield->setPosition(10, y);
    m_pOptions->addItem(pTextfield);
    pSelectKey = new SelectKey(Settings::getKey_screenshot());
    pSelectKey->setTooltipText(tr("Key for taking an screensho."));
    pSelectKey->setPosition(sliderOffset - 130, y);
    connect(pSelectKey.get(), &SelectKey::sigKeyChanged, Settings::getInstance(), &Settings::setKey_screenshot, Qt::QueuedConnection);
    m_pOptions->addItem(pSelectKey);
    y += 40;

    m_pOptions->setContentHeigth(20 + y);
    
}
