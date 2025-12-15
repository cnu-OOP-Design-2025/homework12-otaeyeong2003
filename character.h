#pragma once
#include <iostream>
#include <string>
#include <memory>
#include <stdexcept>
#include "logger.h"

using namespace std;

enum class CharacterType {
    Knight,
    Wizard,
    Archer,
    Unknown
};

class Character {
protected:
    string description;
    CharacterType type;

public:
    Character() : type(CharacterType::Unknown) {}

    virtual string getDescription() const {
        return description;
    }

    virtual int getAttack() const = 0;
    virtual int getSpeed() const = 0;
    virtual int getDefense() const = 0;

    virtual CharacterType getType() const {
        return type;
    }

    virtual ~Character() {
        if (type != CharacterType::Unknown) {
            cout << "Delete Character: " << description << endl;
        }
    }
};

/* ================= 기본 캐릭터 ================= */

class Knight : public Character {
public:
    Knight() {
        description = "Knight";
        type = CharacterType::Knight;
        Logger::getInstance()->log("[Create] Knight");
    }

    int getAttack() const override { return 15; }
    int getSpeed() const override { return 8; }
    int getDefense() const override { return 20; }
};

class Wizard : public Character {
public:
    Wizard() {
        description = "Wizard";
        type = CharacterType::Wizard;
        Logger::getInstance()->log("[Create] Wizard");
    }

    int getAttack() const override { return 20; }
    int getSpeed() const override { return 10; }
    int getDefense() const override { return 10; }
};

class Archer : public Character {
public:
    Archer() {
        description = "Archer";
        type = CharacterType::Archer;
        Logger::getInstance()->log("[Create] Archer");
    }

    int getAttack() const override { return 18; }
    int getSpeed() const override { return 15; }
    int getDefense() const override { return 8; }
};

/* ================= Decorator ================= */

class EquipDeco : public Character {
protected:
    shared_ptr<Character> base;

public:
    EquipDeco(shared_ptr<Character> c, const string& item)
        : base(c) {
        Logger::getInstance()->log(
            "[Trying to Equip] " + c->getDescription() + " + " + item
        );
    }

    CharacterType getType() const override {
        return base->getType();
    }
};

/* ================= 장비 ================= */

class Armor : public EquipDeco {
public:
    Armor(shared_ptr<Character> c)
        : EquipDeco(c, "Armor") {}

    string getDescription() const override {
        return base->getDescription() + " + Armor";
    }

    int getAttack() const override {
        return base->getAttack();
    }

    int getSpeed() const override {
        return base->getSpeed() - 2;
    }

    int getDefense() const override {
        return base->getDefense() + 10;
    }
};

class Boots : public EquipDeco {
public:
    Boots(shared_ptr<Character> c)
        : EquipDeco(c, "Boots") {}

    string getDescription() const override {
        return base->getDescription() + " + Boots";
    }

    int getAttack() const override {
        return base->getAttack();
    }

    int getSpeed() const override {
        return base->getSpeed() + 5;
    }

    int getDefense() const override {
        return base->getDefense();
    }
};

class Sword : public EquipDeco {
public:
    Sword(shared_ptr<Character> c)
        : EquipDeco(c, "Sword") {}

    string getDescription() const override {
        return base->getDescription() + " + Sword";
    }

    int getAttack() const override {
        return base->getAttack() + 10;
    }

    int getSpeed() const override {
        return base->getSpeed();
    }

    int getDefense() const override {
        return base->getDefense();
    }
};

class Staff : public EquipDeco {
public:
    Staff(shared_ptr<Character> c)
        : EquipDeco(c, "Staff") {
        if (c->getType() != CharacterType::Wizard) {
            throw invalid_argument("Staff requires Wizard");
        }
    }

    string getDescription() const override {
        return base->getDescription() + " + Staff";
    }

    int getAttack() const override {
        return base->getAttack() + 8;
    }

    int getSpeed() const override {
        return base->getSpeed();
    }

    int getDefense() const override {
        return base->getDefense();
    }
};

class Bow : public EquipDeco {
public:
    Bow(shared_ptr<Character> c)
        : EquipDeco(c, "Bow") {
        if (c->getType() != CharacterType::Knight &&
            c->getType() != CharacterType::Archer) {
            throw invalid_argument("Bow requires Archer or Knight");
        }
    }

    string getDescription() const override {
        return base->getDescription() + " + Bow";
    }

    int getAttack() const override {
        return base->getAttack() + 7;
    }

    int getSpeed() const override {
        return base->getSpeed() + 2;
    }

    int getDefense() const override {
        return base->getDefense();
    }
};
