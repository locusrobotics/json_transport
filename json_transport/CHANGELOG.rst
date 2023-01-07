^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
Changelog for package json_transport
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Forthcoming
-----------
* Fix python3 build
* Convert default initialized string to 'null' for json parsing (#15)
  * Convert default initialized string to 'null' for json parsing
  * Lock requirements
* Contributors: Paul Bovbel

0.4.0 (2020-10-02)
------------------
* Pull in jsonschema via requirements.txt (`#14 <https://github.com/locusrobotics/json_transport/issues/14>`_)
* Remove msgpack and add basic jsonschema support (`#13 <https://github.com/locusrobotics/json_transport/issues/13>`_)
  * Drop messagepack for raw string transport of json data
  * Rename field for context
  * Add basic jsonschema support
  * Stray line
  * Fix test
* Contributors: Paul Bovbel

0.3.0 (2019-07-12)
------------------
* Add requirements
* Contributors: Paul Bovbel

0.2.0 (2019-03-18)
------------------
* Remove unused import
* Include static_assert header
* Add include guard
* Update __init_\_.py (`#11 <https://github.com/locusrobotics/json_transport/issues/11>`_)
  Update __init_\_.py to include pack and unpack exports.
* Provide helpers for nested fields (`#10 <https://github.com/locusrobotics/json_transport/issues/10>`_)
* Contributors: Andrew Blakey, Paul Bovbel

0.1.0 (2019-01-16)
------------------

0.0.3 (2018-07-16)
------------------
* decode as utf 8 (`#9 <https://github.com/locusrobotics/json_transport/issues/9>`_)
* Contributors: Andrew Blakey

0.0.2 (2018-06-13)
------------------
* Removed check for no default value since falsy and null values are valid JSON. Added test. (`#8 <https://github.com/locusrobotics/json_transport/issues/8>`_)
* Move nlohmann/json.hpp include (`#7 <https://github.com/locusrobotics/json_transport/issues/7>`_)
* Contributors: Andrew Blakey, Paul Bovbel

0.0.1 (2018-04-06)
------------------
* Initial development (`#1 <https://github.com/locusrobotics/json_transport/issues/1>`_)
  * Initial implementation
  * Binary transport (`#2 <https://github.com/locusrobotics/json_transport/issues/2>`_)
* Contributors: Paul Bovbel
