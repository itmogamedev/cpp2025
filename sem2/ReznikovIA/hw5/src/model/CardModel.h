#pragma once

enum class CardState { FaceDown, FaceUp, Matched };

class CardModel {
 public:
  CardModel(int id, int typeId);
  int id;
  int typeId;
  CardState cardState = CardState::FaceDown;
};
