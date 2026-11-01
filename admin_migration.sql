-- Ejecutar una vez en la base de datos s90_orpdb.
ALTER TABLE `players`
  ADD COLUMN IF NOT EXISTS `jAdmin` TINYINT UNSIGNED NOT NULL DEFAULT 0;

-- Para asignar el primer administrador, reemplaza el nombre con la cuenta del propietario:
-- UPDATE `players` SET `jAdmin` = 5 WHERE `jName` = 'TuNombre_Aqui';
