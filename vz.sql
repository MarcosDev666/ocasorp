-- phpMyAdmin SQL Dump
-- version 5.2.1
-- https://www.phpmyadmin.net/
--
-- Servidor: localhost
-- Tiempo de generación: 10-12-2025 a las 18:53:42
-- Versión del servidor: 10.4.32-MariaDB
-- Versión de PHP: 8.2.12

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
START TRANSACTION;
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8mb4 */;

--
-- Base de datos: `s90_orpdb`
--

-- --------------------------------------------------------

--
-- Estructura de tabla para la tabla `players`
--

CREATE TABLE `players` (
  `id` int(10) UNSIGNED NOT NULL,
  `jName` varchar(24) NOT NULL,
  `jPass` varchar(18) NOT NULL,
  `jGmail` varchar(48) NOT NULL,
  `jIP_reg` varchar(22) NOT NULL,
  `jDateRegister` datetime NOT NULL,
  `jLastConnexion` datetime NOT NULL,
  `jCash` int(11) DEFAULT 0,
  `jBankMoney` int(11) DEFAULT 0,
  `jScore` int(11) DEFAULT 0,
  `jSkin` int(11) DEFAULT 0,
  `jState` int(11) DEFAULT 0,
  `jAdmin` tinyint(3) UNSIGNED NOT NULL DEFAULT 0,
  `jJob` tinyint(3) UNSIGNED NOT NULL DEFAULT 0,
  `jJobLevel` tinyint(3) UNSIGNED NOT NULL DEFAULT 1,
  `jJobXP` smallint(5) UNSIGNED NOT NULL DEFAULT 0,
  `jFaction` tinyint(3) UNSIGNED NOT NULL DEFAULT 0,
  `jFactionRank` tinyint(3) UNSIGNED NOT NULL DEFAULT 0,
  `jHunger` tinyint(3) UNSIGNED NOT NULL DEFAULT 100,
  `jThirst` tinyint(3) UNSIGNED NOT NULL DEFAULT 100,
  `jGender` int(11) NOT NULL,
  `jAge` int(11) NOT NULL,
  `jAccent` int(11) NOT NULL,
  `jPosX` float DEFAULT 0,
  `jPosY` float DEFAULT 0,
  `jPosZ` float DEFAULT 0,
  `jRot` float DEFAULT 0,
  `jHealth` float DEFAULT 100,
  `jArmour` float DEFAULT 0
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

--
-- Volcado de datos para la tabla `players`
--

INSERT INTO `players` (`id`, `jName`, `jPass`, `jGmail`, `jIP_reg`, `jDateRegister`, `jLastConnexion`, `jCash`, `jBankMoney`, `jScore`, `jSkin`, `jState`, `jGender`, `jAge`, `jAccent`, `jPosX`, `jPosY`, `jPosZ`, `jRot`, `jHealth`, `jArmour`) VALUES
(4, 'Ocaso_Pa', 'Ocaso6218', '', '127.0.0.1', '0000-00-00 00:00:00', '0000-00-00 00:00:00', 5000, 1000, 0, 250, 0, 1, 30, 0, 1831.38, -1823.58, 15.4279, 245.88, 100, 0);

--
-- Índices para tablas volcadas
--

--
-- Indices de la tabla `players`
--
ALTER TABLE `players`
  ADD PRIMARY KEY (`id`);

--
-- AUTO_INCREMENT de las tablas volcadas
--

--
-- AUTO_INCREMENT de la tabla `players`
--
ALTER TABLE `players`
  MODIFY `id` int(10) UNSIGNED NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=5;

CREATE TABLE `player_inventory` (
  `player_id` int(10) UNSIGNED NOT NULL,
  `slot` tinyint(3) UNSIGNED NOT NULL,
  `item_id` smallint(5) UNSIGNED NOT NULL DEFAULT 0,
  `amount` smallint(5) UNSIGNED NOT NULL DEFAULT 0,
  PRIMARY KEY (`player_id`, `slot`),
  CONSTRAINT `fk_player_inventory_player`
    FOREIGN KEY (`player_id`) REFERENCES `players` (`id`) ON DELETE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

CREATE TABLE `player_vehicles` (
  `id` int(10) UNSIGNED NOT NULL AUTO_INCREMENT,
  `owner_id` int(10) UNSIGNED NOT NULL,
  `model` smallint(5) UNSIGNED NOT NULL,
  `paid` tinyint(1) NOT NULL DEFAULT 0,
  `stored` tinyint(1) NOT NULL DEFAULT 1,
  `created_at` timestamp NOT NULL DEFAULT current_timestamp(),
  PRIMARY KEY (`id`),
  KEY `idx_player_vehicles_owner` (`owner_id`),
  CONSTRAINT `fk_player_vehicles_owner`
    FOREIGN KEY (`owner_id`) REFERENCES `players` (`id`) ON DELETE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

CREATE TABLE `player_houses` (
  `id` smallint(5) UNSIGNED NOT NULL,
  `owner_id` int(10) UNSIGNED DEFAULT NULL,
  PRIMARY KEY (`id`),
  UNIQUE KEY `uq_player_houses_owner` (`owner_id`),
  CONSTRAINT `fk_player_houses_owner`
    FOREIGN KEY (`owner_id`) REFERENCES `players` (`id`) ON DELETE SET NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

INSERT INTO `player_houses` (`id`, `owner_id`) VALUES
  (1, NULL),
  (2, NULL),
  (3, NULL),
  (4, NULL),
  (5, NULL);
COMMIT;

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
