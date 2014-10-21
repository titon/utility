<?hh // strict
/**
 * @copyright   2010-2013, The Titon Project
 * @license     http://opensource.org/licenses/bsd-license.php
 * @link        http://titon.io
 */

namespace Titon\Utility\State;

use Titon\Utility\Col;
use Titon\Utility\Converter;

type GlobalMap = ImmMap<string, mixed>;

class Request {

    /**
     * Immutable data set.
     *
     * @type \Titon\Utility\State\GlobalMap
     */
    protected static GlobalMap $_data = Map {};

    /**
     * Return the entire global collection.
     *
     * @return \Titon\Utility\State\GlobalMap
     */
    public static function all(): GlobalMap {
        return static::$_data;
    }

    /**
     * Return a value based on a dot notated path. If no value is found, return a default value.
     *
     * @param string $key
     * @param mixed $default
     * @return mixed
     */
    public static function get(string $key, mixed $default = null): mixed {
        $value = Col::get(static::$_data, $key);

        if ($value === null) {
            return $default;
        }

        return $value;
    }

    /**
     * Return true if a key exists within the collection.
     * Supports a dot notated path for nested collections.
     *
     * @param string $key
     * @return bool
     */
    public static function has(string $key): bool {
        return Col::has(static::$_data, $key);
    }

    /**
     * Initialize the class by supplying an array of data that recursively gets converted to a map.
     *
     * @param array<string, mixed> $global
     */
    public static function initialize(array<string, mixed> $global): void {
        static::$_data = Converter::toMap($global);
    }

}