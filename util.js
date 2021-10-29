function random(min, max) { return Math.floor(Math.random() * (max - min + 1) ) + min;}
    
Object.prototype.and = function (run) {
  run(this);
  return this;
};

let dynamicStyles = null;

function injectCss(body) {
  if (!dynamicStyles) {
    dynamicStyles = document.createElement('style');
    dynamicStyles.type = 'text/css';
    document.head.appendChild(dynamicStyles);
  }

  dynamicStyles.sheet.insertRule(body, dynamicStyles.length);
}

function miniBoxie (){
  this.image = undefined;
  this.jumpHeight = 15;
  this.jumpSpeed = 0.4;
  this.walkSpeed = 10;
  this.waitTillSpawn = 0;
  this.create = function (){
    var newBoxie = document.createElement("span");
    newBoxie.style.animation = `boxie-hop-${this.jumpHeight} ${this.jumpSpeed}s ease infinite, boxie-walk ${this.walkSpeed}s ease infinite`;
    if (this.image != undefined){
      newBoxie.style.background = `url(${this.image})  0/100% no-repeat`;
    }
    
    injectCss(`@keyframes boxie-hop-${this.jumpHeight} {
      from { bottom: 0px; }
      50% { bottom: ${this.jumpHeight}px; }
      to { bottom: 0px; }
    }`);
    
    return newBoxie;
  };
  
  this.append = function(objectLocation, boxie){
    objectLocation.append(boxie);
  }
}

for (var index = 0; index < 50; index++){
  var boxie = new miniBoxie();
  boxie.walkSpeed = random(2, 40);
  boxie.jumpHeight = random(15, 80);
  boxie.append(document.querySelector("boxies"), boxie.create());
};