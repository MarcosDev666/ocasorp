-- Ejecutar una sola vez en s90_orpdb antes de iniciar el gamemode actualizado.
CREATE TABLE IF NOT EXISTS `player_vehicles` (
  `id` INT(10) UNSIGNED NOT NULL AUTO_INCREMENT,
  `owner_id` INT(10) UNSIGNED NOT NULL,
  `model` SMALLINT UNSIGNED NOT NULL,
  `paid` TINYINT(1) NOT NULL DEFAULT 0,
  `stored` TINYINT(1) NOT NULL DEFAULT 1,
  `created_at` TIMESTAMP NOT NULL DEFAULT CURRENT_TIMESTAMP,
  PRIMARY KEY (`id`),
  KEY `idx_player_vehicles_owner` (`owner_id`),
  CONSTRAINT `fk_player_vehicles_owner`
    FOREIGN KEY (`owner_id`) REFERENCES `players` (`id`) ON DELETE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

CREATE TABLE IF NOT EXISTS `player_houses` (
  `id` SMALLINT UNSIGNED NOT NULL,
  `owner_id` INT(10) UNSIGNED DEFAULT NULL,
  PRIMARY KEY (`id`),
  UNIQUE KEY `uq_player_houses_owner` (`owner_id`),
  CONSTRAINT `fk_player_houses_owner`
    FOREIGN KEY (`owner_id`) REFERENCES `players` (`id`) ON DELETE SET NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

INSERT IGNORE INTO `player_houses` (`id`, `owner_id`) VALUES
  (1, NULL),
  (2, NULL),
  (3, NULL),
  (4, NULL),
  (5, NULL);
