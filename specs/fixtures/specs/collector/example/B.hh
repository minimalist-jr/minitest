<?hh //strict

namespace specify\fixtures\collector\example;

use specify\Specification;

class B implements Specification
{

    <<Example("example2")>>
    public function example2() : void
    {
    }

    public function example3() : void
    {
    }

}