std::shared_ptr<Entity> enemy = std::shared_ptr<Entity>(new si::EnemyShip("./assets/images/enemy.png"));
this->addEntity(enemy);

enemy->setRotation(180);
enemy->setPosition(50, 50);