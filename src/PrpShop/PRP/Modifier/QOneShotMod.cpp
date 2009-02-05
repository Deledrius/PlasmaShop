#include "QOneShotMod.h"

#include <QLabel>
#include <QGroupBox>
#include <QGridLayout>
#include "../../../QPlasma.h"

QOneShotMod::QOneShotMod(plCreatable* pCre, QWidget* parent)
           : QCreatable(pCre, kOneShotMod, parent)
{
    plOneShotMod* obj = (plOneShotMod*)fCreatable;

    fSynchObjLink = new QCreatableLink(this, false);
    fSynchObjLink->setText(tr("Synch Flags"));
    fSynchObjLink->setCreatable(obj);
    fSynchObjLink->setForceType(kSynchedObject);

    QGroupBox* grpFlags = new QGroupBox(tr("OneShot Flags"), this);
    QGridLayout* layFlags = new QGridLayout(grpFlags);
    layFlags->setVerticalSpacing(0);
    layFlags->setHorizontalSpacing(8);
    fDrivable = new QCheckBox(tr("Drivable"), grpFlags);
    fReversable = new QCheckBox(tr("Reversable"), grpFlags);
    fSmartSeek = new QCheckBox(tr("Smart Seek"), grpFlags);
    fNoSeek = new QCheckBox(tr("No Seek"), grpFlags);
    fDrivable->setChecked(obj->isDrivable());
    fReversable->setChecked(obj->isReversable());
    fSmartSeek->setChecked(obj->getSmartSeek());
    fNoSeek->setChecked(obj->getNoSeek());
    layFlags->addWidget(fDrivable, 0, 0);
    layFlags->addWidget(fReversable, 1, 0);
    layFlags->addWidget(fSmartSeek, 0, 1);
    layFlags->addWidget(fNoSeek, 1, 1);

    fAnimName = new QLineEdit(this);
    fAnimName->setText(~obj->getAnimName());

    fSeekDuration = new QDoubleSpinBox(this);
    fSeekDuration->setRange(-2147483648.0, 2147483647.0);
    fSeekDuration->setDecimals(3);
    fSeekDuration->setSingleStep(0.1);
    fSeekDuration->setValue(obj->getSeekDuration());

    QGridLayout* layout = new QGridLayout(this);
    layout->setContentsMargins(8, 8, 8, 8);
    layout->addWidget(fSynchObjLink, 0, 0, 1, 2);
    layout->addWidget(grpFlags, 1, 0, 1, 2);
    layout->addWidget(new QLabel(tr("Animation:"), this), 2, 0);
    layout->addWidget(fAnimName, 2, 1);
    layout->addWidget(new QLabel(tr("Seek Duration:"), this), 3, 0);
    layout->addWidget(fSeekDuration, 3, 1);
}

void QOneShotMod::saveDamage()
{
    plOneShotMod* obj = (plOneShotMod*)fCreatable;

    obj->setDrivable(fDrivable->isChecked());
    obj->setReversable(fReversable->isChecked());
    obj->setSmartSeek(fSmartSeek->isChecked());
    obj->setNoSeek(fNoSeek->isChecked());

    obj->setAnimName(~fAnimName->text());
    obj->setSeekDuration(fSeekDuration->value());
}