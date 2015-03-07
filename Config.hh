<?hh // strict
/**
 * @copyright   2010-2015, The Titon Project
 * @license     http://opensource.org/licenses/bsd-license.php
 * @link        http://titon.io
 */

namespace Titon\Utility;

use Titon\Io\Reader;

/**
 * Stores the current configuration options for the application.
 * Configuration can be loaded from multiple sources including environment, bootstraps and internal system classes.
 * Various readers can be used to import specific configuration files.
 *
 * @package Titon\Utility
 */
class Config {

    /**
     * Current loaded configuration.
     *
     * @var \Titon\Utility\ConfigMap
     */
    protected static ConfigMap $config = Map {};

    /**
     * Add a value to a key. If the value is not a vector, make it one.
     *
     * @param string $key
     * @param mixed $value
     */
    public static function add(string $key, mixed $value): void {
        $data = Col::toVector(static::get($key, Vector {}));
        $data[] = $value;

        static::set($key, $data);
    }

    /**
     * Return all configuration.
     *
     * @return \Titon\Utility\ConfigMap
     */
    public static function all(): ConfigMap {
        return static::$config;
    }

    /**
     * Get the currently defined encoding for the application.
     *
     * @return string
     */
    public static function encoding(): string {
        return (string) static::get('app.encoding') ?: 'UTF-8';
    }

    /**
     * Flush configuration by removing all settings.
     */
    public static function flush(): void {
        static::$config->clear();
    }

    /**
     * Grab a value from the current configuration.
     *
     * @param string $key
     * @param mixed $default
     * @return mixed
     */
    public static function get(string $key, mixed $default = null): mixed {
        $value = Col::get(static::$config, $key);

        if ($value === null) {
            return $default;
        }

        return $value;
    }

    /**
     * Checks to see if a key exists within the current configuration.
     *
     * @param string $key
     * @return bool
     */
    public static function has(string $key): bool {
        return Col::has(static::$config, $key);
    }

    /**
     * Loads a user created file into the configuration class.
     * Uses the defined reader to parse the file.
     *
     * @param string $key
     * @param \Titon\Io\Reader $reader
     */
    public static function load(string $key, Reader $reader): void {
        static::$config[$key] = $reader->readResource();
    }

    /**
     * Grabs the defined project name.
     *
     * @return string
     */
    public static function name(): string {
        return (string) static::get('app.name', '');
    }

    /**
     * Remove a value from the config.
     *
     * @param string $key
     */
    public static function remove(string $key): void {
        Col::remove(static::$config, $key);
    }

    /**
     * Get the currently defined salt for the application.
     *
     * @return string
     */
    public static function salt(): string {
        return (string) static::get('app.salt', '');
    }

    /**
     * Add values to the current loaded configuration.
     *
     * @param string $key
     * @param mixed $value
     */
    public static function set(string $key, mixed $value): void {
        Col::set(static::$config, $key, $value);
    }

}
