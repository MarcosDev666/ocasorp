-- Selecciona primero la base de datos correcta y haz una copia de seguridad.
-- Compatible con MySQL/MariaDB: detecta columnas e indice existentes para que
-- se pueda reanudar si una migracion anterior se interrumpio.
-- Las contrasenas antiguas se convierten a SHA-256 + sal al primer login valido.

ALTER TABLE `players` MODIFY COLUMN `jPass` VARCHAR(128) NOT NULL;

SET @ocaso_sql = IF(
  (SELECT COUNT(*) FROM information_schema.columns
   WHERE table_schema = DATABASE() AND table_name = 'players'
     AND column_name = 'jPassSalt') = 0,
  'ALTER TABLE `players` ADD COLUMN `jPassSalt` VARCHAR(64) NULL AFTER `jPass`',
  'SELECT 1'
);
PREPARE ocaso_stmt FROM @ocaso_sql;
EXECUTE ocaso_stmt;
DEALLOCATE PREPARE ocaso_stmt;

UPDATE `players` SET `jPassSalt` = '' WHERE `jPassSalt` IS NULL;
ALTER TABLE `players` MODIFY COLUMN `jPassSalt` VARCHAR(64) NOT NULL DEFAULT '';

SET @ocaso_sql = IF(
  (SELECT COUNT(*) FROM information_schema.columns
   WHERE table_schema = DATABASE() AND table_name = 'players'
     AND column_name = 'jPhone') = 0,
  'ALTER TABLE `players` ADD COLUMN `jPhone` INT UNSIGNED NOT NULL DEFAULT 0',
  'SELECT 1'
);
PREPARE ocaso_stmt FROM @ocaso_sql;
EXECUTE ocaso_stmt;
DEALLOCATE PREPARE ocaso_stmt;

-- Asigna numeros tambien a las cuentas que aun no iniciaron sesion.
UPDATE `players` SET `jPhone` = 55000000 + `id` WHERE `jPhone` = 0;

SET @ocaso_sql = IF(
  (SELECT COUNT(*) FROM information_schema.statistics
   WHERE table_schema = DATABASE() AND table_name = 'players'
     AND index_name = 'idx_players_phone') = 0,
  'CREATE INDEX `idx_players_phone` ON `players` (`jPhone`)',
  'SELECT 1'
);
PREPARE ocaso_stmt FROM @ocaso_sql;
EXECUTE ocaso_stmt;
DEALLOCATE PREPARE ocaso_stmt;

CREATE TABLE IF NOT EXISTS `phone_messages` (
  `id` INT(10) UNSIGNED NOT NULL AUTO_INCREMENT,
  `sender_id` INT(10) UNSIGNED NOT NULL,
  `receiver_id` INT(10) UNSIGNED NOT NULL,
  `body` VARCHAR(160) NOT NULL,
  `sent_at` TIMESTAMP NOT NULL DEFAULT CURRENT_TIMESTAMP,
  PRIMARY KEY (`id`),
  KEY `idx_phone_messages_receiver` (`receiver_id`, `id`),
  KEY `idx_phone_messages_sender` (`sender_id`),
  CONSTRAINT `fk_phone_messages_sender`
    FOREIGN KEY (`sender_id`) REFERENCES `players` (`id`) ON DELETE CASCADE,
  CONSTRAINT `fk_phone_messages_receiver`
    FOREIGN KEY (`receiver_id`) REFERENCES `players` (`id`) ON DELETE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;
