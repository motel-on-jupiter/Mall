/**
 * Copyright (C) 2014 The Motel on Jupiter
 */
#include "core/scene/ConvenienceStoreScene.h"
#include <vector>
#include "core/actor/Walker.h"
#include "core/prop/AutomaticDoor.h"
#include "core/prop/ShopShelf.h"
#include "mojgame/auxiliary/csyntax_aux.h"
#include "mojgame/includer/gl_include.h"
#include "mojgame/logging/Logger.h"
#include "mojgame/navigation/Waypoint.h"
#include "mojgame/sampler/color_sample.h"

ConvenienceStoreAttendant::ConvenienceStoreAttendant(const glm::vec2 &pos)
    : MallHuman(pos, 0.0f, mojgame::X11Color::kOrange) {
}

ConvenienceStoreCustomer *ConvenienceStoreCustomer::Create(
    ConvenienceStoreStage &stage, std::vector<ShopShelf *> shelfs,
    std::string wanteditem, unsigned int wantednum) {
  for (auto it = shelfs.begin(); it != shelfs.end(); ++it) {
    ShopShelf *shelf = *it;
    if (shelf->stockitem() == wanteditem) {
      const mojgame::Waypoint &cashierpoint = *stage.GetCashierWaypoint(
          rand() % stage.GetCashierNum());
      return new ConvenienceStoreCustomer(stage.const_graph(),
                                          stage.GetPotalWaypoint(),
                                          shelf->waypoint(), cashierpoint,
                                          stage.GetExitWaypoint(), wanteditem,
                                          wantednum);
    }
  }
  return nullptr;
}

ConvenienceStoreCustomer::ConvenienceStoreCustomer(
    const mojgame::WaypointGraph &graph, const mojgame::Waypoint &potalpoint,
    const mojgame::Waypoint &wantedpoint, const mojgame::Waypoint &cashierpoint,
    const mojgame::Waypoint &exitpoint, std::string wanteditem,
    unsigned int wantednum)
    : Walker(glm::radians(90.0f), graph, potalpoint, wantedpoint),
      potalpoint_(potalpoint),
      wantedpoint_(wantedpoint),
      cashierpoint_(cashierpoint),
      exitpoint_(exitpoint),
      wanteditem_(wanteditem),
      wantednum_(wantednum) {
}

int ConvenienceStoreCustomer::Update(float elapsed_time) {
  // Update the motion
  Walker::Update(elapsed_time);

  // Re-routing
  if (HasReached() && !(navi().rerouting())) {
    if (lastgoal() == &wantedpoint_) {
      Reroute(cashierpoint_);
    } else if (lastgoal() == &cashierpoint_) {
      Reroute(exitpoint_);
    } else if (lastgoal() == &exitpoint_) {
      return 1;
    } else {
      assert(false);
    }
  }
  return 0;
}

const size_t ConvenienceStoreStage::kPortalWaypointIdx = 4;
const size_t ConvenienceStoreStage::kCashierWaypointIdxTbl[] = { 8, 9 };
const size_t ConvenienceStoreStage::kExitWaypointIdx = 6;

ConvenienceStoreStage::ConvenienceStoreStage()
    : MallStage() {
}

ConvenienceStoreStage::~ConvenienceStoreStage() {
}

const glm::vec2 ConvenienceStoreStage::kWaypointPositionTbl[] = { glm::vec2(
    8.0f, 5.0f), glm::vec2(10.0f, 5.0f), glm::vec2(12.0f, 5.0f), glm::vec2(
    14.0f, 5.0f), glm::vec2(6.0f, 8.6f), glm::vec2(8.0f, 8.6f), glm::vec2(6.0f,
                                                                          9.4f),
    glm::vec2(8.0f, 9.4f), glm::vec2(10.0f, 9.4f), glm::vec2(12.0f, 9.4f),
    glm::vec2(14.0f, 9.4f), };

int ConvenienceStoreStage::Initialize(const glm::vec2 &size) {
  // Call the base-class method
  int ret = MallStage::Initialize(size);
  if (ret != 0) {
    return ret;
  }

  // Create the way-points
  for (int i = 0; i < ARRAYSIZE(kWaypointPositionTbl); ++i) {
    mojgame::Waypoint *point = new mojgame::Waypoint(kWaypointPositionTbl[i]);
    if (point == nullptr) {
      mojgame::LOGGER().Error(
          "Failed to allocate the waypoint object (idx: %d)", i);
      graph().Clear();
      return -1;
    }
    graph().AddPoint(point);
  }
  graph().points()[0]->AddNextPoint(graph().points()[1]);
  graph().points()[0]->AddNextPoint(graph().points()[5]);
  graph().points()[1]->AddNextPoint(graph().points()[0]);
  graph().points()[1]->AddNextPoint(graph().points()[2]);
  graph().points()[1]->AddNextPoint(graph().points()[8]);
  graph().points()[2]->AddNextPoint(graph().points()[1]);
  graph().points()[2]->AddNextPoint(graph().points()[3]);
  graph().points()[3]->AddNextPoint(graph().points()[2]);
  graph().points()[2]->AddNextPoint(graph().points()[9]);
  graph().points()[3]->AddNextPoint(graph().points()[10]);
  graph().points()[4]->AddNextPoint(graph().points()[5]);
  graph().points()[5]->AddNextPoint(graph().points()[0]);
  graph().points()[5]->AddNextPoint(graph().points()[7]);
  graph().points()[7]->AddNextPoint(graph().points()[6]);
  graph().points()[7]->AddNextPoint(graph().points()[5]);
  graph().points()[7]->AddNextPoint(graph().points()[8]);
  graph().points()[8]->AddNextPoint(graph().points()[1]);
  graph().points()[8]->AddNextPoint(graph().points()[7]);
  graph().points()[8]->AddNextPoint(graph().points()[9]);
  graph().points()[9]->AddNextPoint(graph().points()[2]);
  graph().points()[9]->AddNextPoint(graph().points()[8]);
  graph().points()[9]->AddNextPoint(graph().points()[10]);
  graph().points()[10]->AddNextPoint(graph().points()[3]);
  graph().points()[10]->AddNextPoint(graph().points()[9]);
  return 0;
}

void ConvenienceStoreStage::Finalize() {
  graph().Clear();
}

inline size_t ConvenienceStoreStage::GetCashierNum() const {
  return ARRAYSIZE(kCashierWaypointIdxTbl);
}

inline const mojgame::Waypoint &ConvenienceStoreStage::GetPotalWaypoint() const {
  return *(const_graph().points().at(kPortalWaypointIdx));
}

inline const mojgame::Waypoint *ConvenienceStoreStage::GetCashierWaypoint(
    size_t idx) const {
  if (idx >= GetCashierNum()) {
    return nullptr;
  }
  return const_graph().points().at(kCashierWaypointIdxTbl[idx]);
}

inline const mojgame::Waypoint &ConvenienceStoreStage::GetExitWaypoint() const {
  return *(const_graph().points().at(kExitWaypointIdx));
}

ConvenienceStoreScene::ConvenienceStoreScene()
    : MallBaseGameScene("Convenience Store"),
      initialized_(false),
      stage_(),
      autodoor_(nullptr),
      shelfs_(),
      attendants_(),
      customers_() {
}

ConvenienceStoreScene::~ConvenienceStoreScene() {
}

std::string ConvenienceStoreScene::kShopItemList[] = { "Juice", "Canned Coffee",
    "Beer", "Magazine", "Comics", "Rice Ball", "Packed Lunch", "Ice Cream",
    "Hair Spray", "Toothbrush", "Stationary", "Under Ware", "Instant Noodle",
    "Dry Cell", "Potate Chips", "Candy", "Dried Cuttlefish", "Bar Of Chocolate",
    "Desert", "Bread", };

const ConvenienceStoreScene::ShelfInitParam ConvenienceStoreScene::kShelfInitParamTbl[] =
    { { glm::vec2(9.0f, 4.0f), glm::radians(0.0f), glm::vec2(2.0f, 0.75f),
        "Juice", 50, 0 }, { glm::vec2(11.0f, 4.0f), glm::radians(0.0f),
        glm::vec2(2.0f, 0.75f), "Canned Coffee", 50, 1 }, { glm::vec2(13.0f,
                                                                      4.0f),
        glm::radians(0.0f), glm::vec2(2.0f, 0.75f), "Beer", 50, 2 }, {
        glm::vec2(7.25f, 5.5f), glm::radians(90.0f), glm::vec2(1.75f, 0.3f),
        "Magazine", 30, 0 }, { glm::vec2(7.25f, 7.25f), glm::radians(90.0f),
        glm::vec2(1.75f, 0.3f), "Comics", 50, 5 }, { glm::vec2(15.0f, 5.5f),
        glm::radians(-90.0f), glm::vec2(2.0f, 0.75f), "Rice Ball", 30, 3 }, {
        glm::vec2(15.0f, 7.5f), glm::radians(-90.0f), glm::vec2(2.0f, 0.75f),
        "Packed Lunch", 25, 10 }, { glm::vec2(15.0f, 9.5f), glm::radians(
        -90.0f), glm::vec2(2.0f, 0.75f), "Ice Cream", 30, 10 }, { glm::vec2(
        8.75f, 6.25f), glm::radians(-90.0f), glm::vec2(1.5f, 0.5f),
        "Hair Spray", 15, 0 }, { glm::vec2(8.75f, 7.75f), glm::radians(-90.0f),
        glm::vec2(1.5f, 0.5f), "Toothbrush", 15, 5 }, { glm::vec2(9.25f, 6.25f),
        glm::radians(90.0f), glm::vec2(1.5f, 0.5f), "Stationary", 15, 1 }, {
        glm::vec2(9.25f, 7.75f), glm::radians(90.0f), glm::vec2(1.5f, 0.5f),
        "Under Ware", 15, 8 }, { glm::vec2(10.75f, 6.25f), glm::radians(-90.0f),
        glm::vec2(1.5f, 0.5f), "Instant Noodle", 30, 1 }, { glm::vec2(10.75f,
                                                                      7.75f),
        glm::radians(-90.0f), glm::vec2(1.5f, 0.5f), "Dry Cell", 30, 8 }, {
        glm::vec2(11.25f, 6.25f), glm::radians(90.0f), glm::vec2(1.5f, 0.5f),
        "Potate Chips", 30, 2 }, { glm::vec2(11.25f, 7.75f), glm::radians(
        90.0f), glm::vec2(1.5f, 0.5f), "Candy", 30, 9 },
        { glm::vec2(12.75f, 6.25f), glm::radians(-90.0f), glm::vec2(1.5f, 0.5f),
            "Dried Cuttlefish", 30, 2 }, { glm::vec2(12.75f, 7.75f),
            glm::radians(-90.0f), glm::vec2(1.5f, 0.5f), "Bar Of Chocolate", 30,
            9 }, { glm::vec2(13.25f, 6.25f), glm::radians(90.0f), glm::vec2(
            1.5f, 0.5f), "Desert", 20, 3 }, { glm::vec2(13.25f, 7.75f),
            glm::radians(90.0f), glm::vec2(1.5f, 0.5f), "Bread", 20, 10 }, {
            glm::vec2(-1.0f) },  // sentinel
    };

int ConvenienceStoreScene::Initialize(const glm::vec2 &stage_size) {
  // Initialize the stage
  int ret = stage_.Initialize(stage_size);
  if (ret != 0) {
    mojgame::LOGGER().Error("Failed to initialize the stage");
    return -1;
  }

  AutomaticDoor *autodoor = new AutomaticDoor(glm::vec2(6.75f, 9.0f),
                                              glm::radians(90.0f),
                                              glm::vec2(1.6f, 0.1f));
  if (autodoor == nullptr) {
    mojgame::LOGGER().Error("Failed to create auto door");
    return -1;
  }
  autodoor_ = autodoor;

  for (auto initparam = kShelfInitParamTbl; initparam->pos.x > 0.0f;
      ++initparam) {
    assert(initparam->waypoint < stage_.const_graph().points().size());
    mojgame::Waypoint *waypoint = stage_.const_graph().points()[initparam
        ->waypoint];
    ShopShelf *shelf = new ShopShelf(initparam->pos, initparam->rot,
                                     initparam->scale, initparam->stockitem,
                                     initparam->stocknum, *waypoint);
    if (shelf == nullptr) {
      mojgame::LOGGER().Error("Failed to create shelf");
      return -1;
    }
    shelfs_.push_back(shelf);
  }

  ConvenienceStoreAttendant *attendant = new ConvenienceStoreAttendant(
      glm::vec2(10.0f, 10.5f));
  if (attendant == nullptr) {
    mojgame::LOGGER().Error("Failed to create 1st attendant");
    return -1;
  }
  attendants_.push_back(attendant);
  attendant = new ConvenienceStoreAttendant(glm::vec2(12.0f, 10.5f));
  if (attendant == nullptr) {
    mojgame::LOGGER().Error("Failed to create 2nd attendant");
    return -1;
  }
  attendants_.push_back(attendant);

  // Update the OpenGL flags
  glDisable(GL_LIGHTING);
  glDisable(GL_LIGHT0);

  // Update the flags
  initialized_ = true;
  return 0;
}

void ConvenienceStoreScene::Finalize() {
  if (!initialized_) {
    mojgame::LOGGER().Notice("Ignored the duplicate call to finalize game");
    return;
  }
  for (auto it = attendants_.begin(); it != attendants_.end(); ++it) {
    delete *it;
  }
  attendants_.clear();
  for (auto it = customers_.begin(); it != customers_.end(); ++it) {
    delete *it;
  }
  customers_.clear();
  for (auto it = shelfs_.begin(); it != shelfs_.end(); ++it) {
    delete *it;
  }
  shelfs_.clear();
  delete autodoor_;
  autodoor_ = nullptr;
  stage_.Finalize();
  initialized_ = false;
  return;
}

int ConvenienceStoreScene::Update(float elapsed_time) {
  UNUSED(elapsed_time);

  if (!initialized_) {
    return 1;
  }

  // Generate a walker randomly
  if (glm::linearRand(0.0f, 1.0f) < 0.3f * elapsed_time) {
    std::string &wanteditem = kShopItemList[rand() % ARRAYSIZE(kShopItemList)];
    ConvenienceStoreCustomer *customer = ConvenienceStoreCustomer::Create(
        stage_, shelfs_, wanteditem, 1);
    if (customer == nullptr) {
      mojgame::LOGGER().Error("Failed to create a customer");
      return -1;
    }
    customers_.push_back(customer);
  }

  // Update the objects
  autodoor_->Update(
      elapsed_time,
      const_cast<const mojgame::PlanarEntity **>(reinterpret_cast<mojgame::PlanarEntity **>(customers_
          .data())),
      customers_.size());
  for (auto it = customers_.begin(); it != customers_.end();) {
    if ((*it)->Update(elapsed_time) == 1) {
      delete *it;
      it = customers_.erase(it);
    } else {
      ++it;
    }
  }
  return 0;
}

int ConvenienceStoreScene::Draw() {
  if (!initialized_) {
    return 1;
  }
  stage_.Draw();
  autodoor_->Draw();
  for (auto it = shelfs_.begin(); it != shelfs_.end(); ++it) {
    (*it)->Draw();
  }
  for (auto it = attendants_.begin(); it != attendants_.end(); ++it) {
    (*it)->Draw();
  }
  for (auto it = customers_.begin(); it != customers_.end(); ++it) {
    (*it)->Draw();
  }
  return 0;
}

int ConvenienceStoreScene::OnMouseButtonDown(unsigned char button,
                                             const glm::vec2 &cursor_pos) {
  UNUSED(button);
  UNUSED(cursor_pos);

  return 0;
}
