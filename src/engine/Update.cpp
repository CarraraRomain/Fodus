#include "Update.hpp"

using namespace engine;

Update::Update(): new_state(0) {

}

Update::~Update() {

}


bool Update::isListUpdate() const {
    return pending_list;
}

bool Update::isPlayerTurnUpdate() const {
    return pending_next_player;
}

bool Update::isEndGameUpdate() const {
    return game_end;
}

state::ElementList& Update::getList() {
    return new_list;
}

int Update::getCurrentPlayer() const {
    return current_player;
}

int Update::getEndScore() const {
    return end_score;
}

void Update::setList(state::ElementList list) {


    pending_list = true;
    pending_update = true;
}

void Update::setCurrentPlayerID(int pl) {

	current_player = pl;
    pending_next_player = true;
    pending_update = true;
}

void Update::setPlayer(engine::Player pl) {

    pending_player = true;
    pending_update = true;
}

bool Update::pendingUpdate() const {
    return pending_update;
}

state::Etat Update::getStateUpdate() {
    return new_state;
}

void Update::setNewState(state::Etat e) {
    new_state = e;
    pending_update = true;
    pending_state = true;
}

void Update::clear() {
pending_next_player = false;
    pending_update = false;
    pending_list = false;
    pending_state = false;
    pending_player = false;
    game_end = false;
}

bool Update::isStateUpdate() const {
    return pending_state;
}
