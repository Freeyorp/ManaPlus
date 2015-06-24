/*
 *  The ManaPlus Client
 *  Copyright (C) 2009  The Mana World Development Team
 *  Copyright (C) 2009-2010  Andrei Karas
 *  Copyright (C) 2011-2015  The ManaPlus Developers
 *
 *  This file is part of The ManaPlus Client.
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "gui/windows/textcommandeditor.h"

#include "spellmanager.h"

#include "input/keyboardconfig.h"

#include "gui/models/iconsmodel.h"
#include "gui/models/magicschoolmodel.h"
#include "gui/models/targettypemodel.h"

#include "gui/widgets/button.h"
#include "gui/widgets/containerplacer.h"
#include "gui/widgets/dropdown.h"
#include "gui/widgets/inttextfield.h"
#include "gui/widgets/label.h"
#include "gui/widgets/layoutcell.h"
#include "gui/widgets/radiobutton.h"

#include "utils/delete2.h"

#include "debug.h"

TextCommandEditor::TextCommandEditor(TextCommand *const command) :
    // TRANSLATORS: command editor name
    Window(_("Command Editor"), Modal_false, nullptr, "commandeditor.xml"),
    ActionListener(),
    mIsMagicCommand(command ?
        (command->getCommandType() == TEXT_COMMAND_MAGIC) : false),
    mCommand(command),
    // TRANSLATORS: command editor button
    mIsMagic(new RadioButton(this, _("magic"), "magic", mIsMagicCommand)),
    // TRANSLATORS: command editor button
    mIsOther(new RadioButton(this, _("other"), "magic", !mIsMagicCommand)),
    // TRANSLATORS: command editor label
    mSymbolLabel(new Label(this, _("Symbol:"))),
    mSymbolTextField(new TextField(this)),
    // TRANSLATORS: command editor label
    mCommandLabel(new Label(this, _("Command:"))),
    mCommandTextField(new TextField(this)),
    // TRANSLATORS: command editor label
    mCommentLabel(new Label(this, _("Comment:"))),
    mCommentTextField(new TextField(this)),
    mTargetTypeModel(new TargetTypeModel),
    // TRANSLATORS: command editor label
    mTypeLabel(new Label(this, _("Target Type:"))),
    mTypeDropDown(new DropDown(this, mTargetTypeModel)),
    mIconsModel(new IconsModel),
    // TRANSLATORS: command editor label
    mIconLabel(new Label(this, _("Icon:"))),
    mIconDropDown(new DropDown(this, mIconsModel)),
    // TRANSLATORS: command editor label
    mManaLabel(new Label(this, _("Mana:"))),
    mManaField(new IntTextField(this, 0)),
    // TRANSLATORS: command editor label
    mMagicLvlLabel(new Label(this, _("Magic level:"))),
    mMagicLvlField(new IntTextField(this, 0)),
    mMagicSchoolModel(new MagicSchoolModel),
    // TRANSLATORS: command editor label
    mSchoolLabel(new Label(this, _("Magic School:"))),
    mSchoolDropDown(new DropDown(this, mMagicSchoolModel)),
    // TRANSLATORS: command editor label
    mSchoolLvlLabel(new Label(this, _("School level:"))),
    mSchoolLvlField(new IntTextField(this, 0)),
    // TRANSLATORS: command editor button
    mCancelButton(new Button(this, _("Cancel"), "cancel", this)),
    // TRANSLATORS: command editor button
    mSaveButton(new Button(this, _("Save"), "save", this)),
    // TRANSLATORS: command editor button
    mDeleteButton(new Button(this, _("Delete"), "delete", this)),
    mEnabledKeyboard(keyboard.isEnabled())
{
    const int w = 350;
    const int h = 370;

    keyboard.setEnabled(false);

    setWindowName("TextCommandEditor");
    setDefaultSize(w, h, ImageRect::CENTER);

    mIsMagic->setActionEventId("magic");
    mIsMagic->addActionListener(this);

    mIsOther->setActionEventId("other");
    mIsOther->addActionListener(this);

    mManaField->setRange(0, 500);
    mManaField->setWidth(20);

    mTypeDropDown->setActionEventId("type");
    mTypeDropDown->addActionListener(this);

    mIconDropDown->setActionEventId("icon");
    mIconDropDown->addActionListener(this);
    mIconDropDown->setSelectedString(mCommand->getIcon());

    mMagicLvlField->setRange(0, 5);
    mMagicLvlField->setWidth(20);

    mSchoolDropDown->setActionEventId("school");
    mSchoolDropDown->addActionListener(this);
    mSchoolDropDown->setSelected(0);

    mSchoolLvlField->setRange(0, 5);
    mSchoolLvlField->setWidth(20);

    mSaveButton->adjustSize();
    mCancelButton->adjustSize();
    mDeleteButton->adjustSize();

    if (command)
    {
        if (command->getCommandType() == TEXT_COMMAND_MAGIC)
            showControls(Visible_true);
        else
            showControls(Visible_false);

        mSymbolTextField->setText(command->getSymbol());
        mCommandTextField->setText(command->getCommand());
        mCommentTextField->setText(command->getComment());
        mManaField->setValue(command->getMana());
        mTypeDropDown->setSelected(static_cast<int>(command->getTargetType()));
        mMagicLvlField->setValue(command->getBaseLvl());
        mSchoolDropDown->setSelected(static_cast<int>(command->getSchool())
            - MAGIC_START_ID);
        mSchoolLvlField->setValue(command->getSchoolLvl());
    }

    ContainerPlacer placer;
    placer = getPlacer(0, 0);

    placer(0, 0, mIsMagic, 1);
    placer(2, 0, mIsOther, 1);
    placer(0, 1, mSymbolLabel, 2).setPadding(3);
    placer(2, 1, mSymbolTextField, 3).setPadding(3);
    placer(0, 2, mCommandLabel, 2).setPadding(3);
    placer(2, 2, mCommandTextField, 4).setPadding(3);

    placer(0, 3, mCommentLabel, 2).setPadding(3);
    placer(2, 3, mCommentTextField, 4).setPadding(3);

    placer(0, 4, mTypeLabel, 2).setPadding(3);
    placer(2, 4, mTypeDropDown, 3).setPadding(3);

    placer(0, 5, mIconLabel, 2).setPadding(3);
    placer(2, 5, mIconDropDown, 3).setPadding(3);

    placer(0, 6, mManaLabel, 2).setPadding(3);
    placer(2, 6, mManaField, 3).setPadding(3);
    placer(0, 7, mMagicLvlLabel, 2).setPadding(3);
    placer(2, 7, mMagicLvlField, 3).setPadding(3);

    placer(0, 8, mSchoolLabel, 2).setPadding(3);
    placer(2, 8, mSchoolDropDown, 3).setPadding(3);
    placer(0, 9, mSchoolLvlLabel, 2).setPadding(3);
    placer(2, 9, mSchoolLvlField, 3).setPadding(3);

    placer(0, 10, mSaveButton, 2).setPadding(3);
    placer(2, 10, mCancelButton, 2).setPadding(3);
    placer(4, 10, mDeleteButton, 2).setPadding(3);

    setWidth(w);
    setHeight(h);

    reflowLayout(w);

    center();
}

void TextCommandEditor::postInit()
{
    Window::postInit();
    enableVisibleSound(true);
    setVisible(Visible_true);
}

TextCommandEditor::~TextCommandEditor()
{
    delete2(mIconsModel);
    delete2(mTargetTypeModel);
    delete2(mMagicSchoolModel);
}

void TextCommandEditor::action(const ActionEvent &event)
{
    const std::string &eventId = event.getId();
    if (eventId == "magic")
    {
        mIsMagicCommand = true;
        showControls(Visible_true);
    }
    else if (eventId == "other")
    {
        mIsMagicCommand = false;
        showControls(Visible_false);
    }
    else if (eventId == "save")
    {
        save();
        scheduleDelete();
    }
    else if (eventId == "cancel")
    {
        scheduleDelete();
    }
    else if (eventId == "delete")
    {
        deleteCommand();
        scheduleDelete();
    }
}

void TextCommandEditor::showControls(const Visible show)
{
    mManaField->setVisible(show);
    mManaLabel->setVisible(show);
    mMagicLvlLabel->setVisible(show);
    mMagicLvlField->setVisible(show);
    mSchoolLabel->setVisible(show);
    mSchoolDropDown->setVisible(show);
    mSchoolLvlLabel->setVisible(show);
    mSchoolLvlField->setVisible(show);
}

void TextCommandEditor::scheduleDelete()
{
    keyboard.setEnabled(mEnabledKeyboard);
    Window::scheduleDelete();
}

void TextCommandEditor::save()
{
    if (mIsMagicCommand)
        mCommand->setCommandType(TEXT_COMMAND_MAGIC);
    else
        mCommand->setCommandType(TEXT_COMMAND_TEXT);

    mCommand->setSymbol(mSymbolTextField->getText());
    mCommand->setCommand(mCommandTextField->getText());
    mCommand->setComment(mCommentTextField->getText());
    mCommand->setMana(mManaField->getValue());
    mCommand->setTargetType(
            static_cast<SpellTarget>(mTypeDropDown->getSelected()));
    mCommand->setIcon(mIconDropDown->getSelectedString());
    mCommand->setBaseLvl(mMagicLvlField->getValue());
    mCommand->setSchool(static_cast<MagicSchool>(
            mSchoolDropDown->getSelected() + MAGIC_START_ID));
    mCommand->setSchoolLvl(mSchoolLvlField->getValue());
    if (spellManager)
        spellManager->save();
}

void TextCommandEditor::deleteCommand()
{
    mCommand->setCommandType(TEXT_COMMAND_TEXT);
    mCommand->setSymbol("");
    mCommand->setCommand("");
    mCommand->setComment("");
    mCommand->setMana(0);
    mCommand->setTargetType(NOTARGET);
    mCommand->setIcon("");
    mCommand->setBaseLvl(0);
    mCommand->setSchool(SKILL_MAGIC);
    mCommand->setSchoolLvl(0);
    if (spellManager)
        spellManager->save();
}
