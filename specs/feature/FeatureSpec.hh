<?hh //partial

use specify\feature\Feature;
use specify\feature\FeatureDescription;
use specify\fixtures\example\FeatureExample;
use specify\notifier\NullNotifier;
use \Prophecy\Prophet;
use \Prophecy\Argument;
use \Exception;


describe(Feature::class, function() {
    describe('->verify()', function() {
        context('when passed', function() {
            beforeEach(function() {
                $this->notifier = new NullNotifier();
            });
            it('returns passed result', function() {
                $target = new FeatureExample();
                $featureMethod = new ReflectionMethod($target, 'example1');

                $feature = new Feature($target, $featureMethod);
                $result = $feature->verify($this->notifier);

                expect($result->getDescription())->toBeAnInstanceOf(FeatureDescription::class);
                expect($result->isPassed())->toBeTrue();
                expect($result->isFailed())->toBeFalse();
            });
        });
        context('when failed', function() {
            beforeEach(function() {
                $this->notifier = new NullNotifier();
            });
            it('returns passed result', function() {
                $target = new FeatureExample();
                $featureMethod = new ReflectionMethod($target, 'example3');

                $feature = new Feature($target, $featureMethod);
                $result = $feature->verify($this->notifier);

                expect($result->getDescription())->toBeAnInstanceOf(FeatureDescription::class);
                expect($result->isPassed())->toBeFalse();
                expect($result->isFailed())->toBeTrue();
            });
        });
    });
});
