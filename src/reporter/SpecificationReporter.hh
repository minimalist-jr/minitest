<?hh //strict

/**
 * This file is part of hhspecify.
 *
 * (c) Noritaka Horio <holy.shared.design@gmail.com>
 *
 * This source file is subject to the MIT license that is bundled
 * with this source code in the file LICENSE.
 */

namespace hhspecify\reporter;

use hhspecify\LifeCycleEvent;
use hhspecify\LifeCycleMessageSubscriber;
use hhspecify\event\FeaturePackageStart;
use hhspecify\event\FeatureGroupStart;
use hhspecify\event\FeatureFinish;
use hhspecify\event\FeatureGroupFinish;
use hhspecify\event\FeaturePackageFinish;
use hhspecify\io\ConsoleOutput;
use hhspecify\io\Console;


final class SpecificationReporter implements LifeCycleMessageSubscriber
{

    private int $indentLevel = 0;

    public function __construct(
        private Console $writer = new ConsoleOutput()
    )
    {
    }

    public function receive(LifeCycleEvent $event) : void
    {
        if ($event instanceof FeaturePackageStart) {
            $this->onPackageStart($event);
        } else if ($event instanceof FeatureGroupStart) {
            $this->onGroupStart($event);
        } else if ($event instanceof FeatureFinish) {
            $this->onFeatureFinish($event);
        } else if ($event instanceof FeatureGroupFinish) {
            $this->onGroupFinish($event);
        }
    }

    private function onPackageStart(FeaturePackageStart $event) : void
    {
        $this->writer->writeln("\nPackage: %s\n", $event->getDescription());
        $this->indentLevel++;
    }

    private function onGroupStart(FeatureGroupStart $event) : void
    {
        $indentSpace = str_pad("", $this->indentLevel * 2, " ");

        $this->writer->write($indentSpace . "<white>%s</white>\n", $event->getDescription());
        $this->indentLevel++;
    }

    private function onFeatureFinish(FeatureFinish $event) : void
    {
        $indentSpace = str_pad("", $this->indentLevel * 2, " ");
        $format = "<green>✓</green> <white>%s</white>\n";

        if ($event->isFailed()) {
            $format = "  <red>%s</red>\n";
        } else if ($event->isPending()) {
            $format = "  <lightCyan>%s</lightCyan>\n";
        }

        $this->writer->write($indentSpace . $format, $event->getDescription());
    }

    private function onGroupFinish(FeatureGroupFinish $event) : void
    {
        $this->writer->writeln("");
        $this->indentLevel--;
    }

}
