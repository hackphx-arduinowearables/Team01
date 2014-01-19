var player = $('#player');
function movePlayer (direction, amount) {
  var pp = '+=' + amount + '%';
  var np =  '-=' + amount + '%';
  if (direction === 'up') {player.animate({top: np}, 25);}
  if (direction === 'down') {player.animate({top: pp}, 25);}
  if (direction === 'left') {player.attr('src', 'img/flying_left.png'); player.animate({left: np}, 25);}
  if (direction === 'right') {player.attr('src', 'img/flying_right.png'); player.animate({left: pp}, 25);}
  for (var j = 0; j < 250; j++) {collide(player, $('#obstacle' + (j + 1)));}
}

function collide (a, b) {
  var c = a[0].getBoundingClientRect();
  var d = b[0].getBoundingClientRect();
  return !(
    c.top > d.bottom ||
    c.right < d.left ||
    c.bottom < d.top ||
    c.left > d.right
  );
}

var i = 0;
var loop = setInterval(function () {
  if (i === 249) {
    clearInterval(loop);
    alert('You won the game!!! Congratulations!');
  }
  for (var k = 0; k < 250; k++) {
    var collisions = collide(player, $('#obstacle' + (k + 1)));
    if (collisions) {
      var foo = confirm('Game over! Confirm if you want to play again.');
      if (foo) {window.location.reload();}
      else {window.location.href = 'https://github.com/hackPHX-ArduinoWearables/Team01';}
    }
  }
  var obstacle = $('#obstacle' + (i + 1));
  var randomX = (Math.random() * window.innerWidth) - (window.innerWidth / 100 * 6.25);
  var randomY = (Math.random() * window.innerHeight) - (window.innerHeight / 100 * 6.25);
  obstacle.css('top', randomY);
  obstacle.css('left', randomX);
  obstacle.fadeIn(1250);

  i++;
}, 2500);



$(document).keydown(function () {
  if (event.which === 119 || event.which === 38) {
    return movePlayer('up', 1.25);
  }
  if (event.which === 115 || event.which === 40) {
    return movePlayer('down', 1.25);
  }
  if (event.which === 97 || event.which === 37) {
    return movePlayer('left', 1.25);
  }
  if (event.which === 100 || event.which === 39) {
    return movePlayer('right', 1.25);
  }
});
