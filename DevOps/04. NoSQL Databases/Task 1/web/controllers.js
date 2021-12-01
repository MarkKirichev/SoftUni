var mongoApp = angular.module('mongo', ['ui.bootstrap']);

/**
 * Constructor
 */
function MongoController() {}

MongoController.prototype.onMongo = function() {
    this.scope_.messages.push(this.scope_.msg);
    var value = this.scope_.msg;

    this.http_.get("guestbook.php?cmd=set&key=messages&value=" + value)
            .success(angular.bind(this, function(data) {
                this.scope_.mongoResponse = "Inserted.";
            }));
};

mongoApp.controller('MongoCtrl', function ($scope, $http, $location) {
        $scope.controller = new MongoController();
        $scope.controller.scope_ = $scope;
        $scope.controller.location_ = $location;
        $scope.controller.http_ = $http;

        $scope.controller.http_.get("guestbook.php?cmd=get&key=messages")
            .success(function(data) {
                console.log(data);
                $scope.messages = data.data.split(",");
            });
});
