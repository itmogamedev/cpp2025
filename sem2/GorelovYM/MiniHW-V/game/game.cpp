#include "../engine/index.h"
#include <iostream>

#define RESFOLDER "resources/"
#define WINW 128
#define WINH 128
#define CARDW 32
#define FIELDW 4
#define FIELDSIZE (FIELDW * FIELDW)
#define BGCOLOR 0x222222
#define MAXBADSTEPS 3

template <typename T>
using sptr = std::shared_ptr<T>;

sptr<Image> backside;
sptr<Image> frontsides[8];

struct { bool shown; char id; }
  cards[FIELDSIZE];
char cardsshown = 0;
char badsteps = 0;
char cardfirstpos = 0;
int timer = 0;
int steps = 0;

DeclScene(Main);

Engine engine("Zapominashki", WINW, WINH, 5, []() {
  Resources::Load<Resources::Image>("sCards", RESFOLDER "cards.bmp");
  Resources::Load<Resources::Font>("fDebug", RESFOLDER "debug.font");
  Scene::Switch("Main");
});

void Shuffle() {
  for (int i = 0; i < 32; i++) {
    int card1 = Utilities::RandRange(0, FIELDSIZE - 1);
    int card2 = Utilities::RandRange(0, FIELDSIZE - 1);
    if (cards[card1].shown || cards[card2].shown)
      continue;
    std::swap(cards[card1], cards[card2]);
  }
}

void Renderer(void) {
  Engine::Screen().Fill(BGCOLOR);
  for (int i = 0; i < FIELDSIZE; i++) {
    int px = i % FIELDW * CARDW;
    int py = i / FIELDW * CARDW;
    if (cards[i].shown)
      Engine::Screen().Draw(frontsides[cards[i].id].get(), px, py);
    else
      Engine::Screen().Draw(backside.get(), px, py);
  }
}

static void Init()
{
    backside = Resources::Get<Resources::Image>("sCards")
    ->Cut(0, 0, CARDW, CARDW);

    for (int i = 1; i < 9; i++)
    frontsides[i - 1] = Resources::Get<Resources::Image>("sCards")
      ->Cut(i * CARDW, 0, CARDW, CARDW);

    for (int i = 0; i < 16; i += 2)
    cards[i].id = i / 2,
    cards[i].shown = false,
    cards[i + 1].id = i / 2,
    cards[i + 1].shown = false;

    Shuffle();
  Renderer();
}

static void Update()
{
  char correct = 0;
  for (int i = 0; i < FIELDSIZE; i++)
    if (cards[i].shown)
      correct++;
  if (correct == FIELDSIZE) {
    Engine::Screen().Fill(WINW / 4, WINW / 4, WINW / 2, WINW / 2, 0x111111);
    auto f = Resources::Get<Resources::Font>("fDebug");
    Engine::Screen().Write(f, "STEPS: " + std::to_string(steps),
      WINW / 5 * 2 - 4, WINW / 2 - 2, 0xeeeeee);
    return;
  }

  if (timer) {
    timer--;
    return;
  }
  else
    Renderer();

  if (Input::Mouse(Input::Primary))
  {
    int x = Input::MouseX() / CARDW;
    int y = Input::MouseY() / CARDW;
    int pos = x + y * FIELDW;

    if (!cards[pos].shown) {
      cards[pos].shown = true;
      cardsshown++;
      Renderer();

      if (cardsshown == 1)
        cardfirstpos = pos;

      if (cardsshown == 2) {
        Renderer();
        if (cards[pos].id == cards[cardfirstpos].id)
          badsteps = 0;
        else {
          Renderer();
          timer = 60;
          badsteps++;
          cards[pos].shown = false;
          cards[cardfirstpos].shown = false;
          if (badsteps == MAXBADSTEPS)
            Shuffle(), badsteps = 0;
        }
        
        steps++;
        cardsshown = 0;
      }
    }
  }
}

static void Destroy() { }