<?hh //partial

use hhspecify\event\FeaturePackageFinish;
use hhspecify\result\FeatureResult;
use hhspecify\result\FeatureGroupResult;
use hhspecify\result\FeaturePackageResult;
use hhspecify\io\BufferWriter;
use hhspecify\io\ConsoleOutput;
use hhspecify\util\ProcessingTime;
use hhspecify\reporter\SummaryReporter;


describe(SummaryReporter::class, function() {
    describe('->handle()', function() {
        beforeEach(function() {
            $this->bufferWriter = new BufferWriter();
            $this->consoleOutput = new ConsoleOutput($this->bufferWriter);
            $this->reporter = new SummaryReporter($this->consoleOutput);

            $this->processingTime = new ProcessingTime(1000.0, 2000.0);
        });
        context('when handle example package finish event', function() {
            context('when passed', function() {
                beforeEach(function() {
                    $group = new FeatureGroupResult('foo', Vector {
                        FeatureResult::passed('foo->bar1()')
                    });

                    $packageResult = new FeaturePackageResult('package', ImmVector {
                        $group
                    }, $this->processingTime);

                    $this->event = new FeaturePackageFinish($packageResult);
                });
                it('report verify summary by passed color', function() {
                    expect(() ==> {
                        $this->reporter->receive($this->event);
                    })->toPrint("\e[0;32m1 feature, 0 failures, 0 pending\e[0m\n");
                });
            });
            context('when failed', function() {
                beforeEach(function() {
                    $group = new FeatureGroupResult('foo', Vector {
                        FeatureResult::failed('foo->bar1()')
                    });

                    $packageResult = new FeaturePackageResult('package', ImmVector {
                        $group
                    }, $this->processingTime);

                    $this->event = new FeaturePackageFinish($packageResult);
                });
                it('report verify summary by failed color', function() {
                    expect(() ==> {
                        $this->reporter->receive($this->event);
                    })->toPrint("\e[0;31m1 feature, 1 failures, 0 pending\e[0m\n");
                });
            });
        });
    });
});
