$(document).ready(function(){

    $("#start_game").click(function(){
        //localStorage.clear();
        size = $("input[name='size']:checked").attr("id");
        difficulty = $("input[name='difficulty']:checked").attr("id");
        size = parseInt(size[0] + size[1])
        localStorage.setItem("size", size)
        
        switch(difficulty){
            case "easy":
                speed = 200
                break
            case "medium":
                speed = 100
                break
            case "hard":
                speed = 50
                break
        }
        localStorage.setItem("speed", speed)

        field = new Array(size)
        for(let i = 0; i < size; i++){
            field[i] = new Array(size).fill(0)
        }
        //zmija na polju 0,0
        field[0][0] = 1

        snake = {
            x: 0,
            y: 0,
            next: null
        }
        localStorage.setItem("snake", JSON.stringify(snake))

        //inicijalni komad hrane
        while(true){
            row = Math.floor(Math.random() * size)
            col = Math.floor(Math.random() * size)
            if(field[row][col] != 1){
                field[row][col] = 2
                break;
            }
        }
        localStorage.setItem("field", JSON.stringify(field))
        
        localStorage.setItem("currentResault", 0)
        if(localStorage.getItem("bestResault") == null)
            localStorage.setItem("bestResault", 0)
        if(localStorage.getItem("leaderboard") == null)
            localStorage.setItem("leaderboard", JSON.stringify([]))
        
        window.open("zmijica-igra.html", "_self")
        
    })

    $(document).keydown(function(event){
        speed = parseInt(localStorage.getItem("speed"))
        var keycode = (event.keyCode ? event.keyCode : event.which);
        if(keycode == '37' || keycode == '65'){
            //left
            if(moveSnake("left") == false){
                //saveResault()
                saveResault()
            }else{
                clearInterval(move)
                move = setInterval(moveSnake, speed, "left")
            }
        }else if(keycode == '39' || keycode == '68'){
            //right
            if(moveSnake("right") == false){
                //saveResault()
                saveResault()
            }else{
                clearInterval(move)
                move = setInterval(moveSnake, speed, "right")
            }
        }else if(keycode == '38' || keycode == '87'){
            //up
            if(moveSnake("up") == false){
                //saveResault()
                saveResault()
            }else{
                clearInterval(move)
                move = setInterval(moveSnake, speed, "up")
            }
        }else if(keycode == '40' || keycode == '83'){
            //down
            if(moveSnake("down") == false){
                //saveResault()
                saveResault()
            }else{
                clearInterval(move)
                move = setInterval(moveSnake, speed, "down")
            }
        }
      });

      $("#back").click(function(){
        window.open("zmijica-uputstvo.html", "_self")
      })

      $("#show_resaults").click(function(){
        window.open("zmijica-rezultati.html", "_self")
      })
})

function printTable(){
    size = localStorage.getItem("size")
    field = JSON.parse(localStorage.getItem("field"))
    speed = parseInt(localStorage.getItem("speed"))

    table = document.createElement("table")
    table.style.cssText = "border: 1px solid #B0C4DE"
    for(let i = 0; i < size; i++){
        row = document.createElement("tr")
        for(let j = 0; j < size; j++){
            td = document.createElement("td")
            td.setAttribute("id", i+"-"+j)
            td.style.cssText = "width:30px; height:30px;"
            if(field[i][j] == 1){
                td.style.cssText += "background-color:rgba(0, 61, 219, 1)"
            }else{
                if(i%2 == 1){
                    if(j%2==1)
                        td.style.cssText += "background-color:RGB(52, 58, 64)"
                    else
                        td.style.cssText += "background-color:rgba(43, 43, 43, 1)"
                }else{
                    if(j%2==0)
                        td.style.cssText += "background-color:RGB(52, 58, 64)"
                    else
                        td.style.cssText += "background-color:rgba(43, 43, 43, 1)"
                }
                if(field[i][j] == 2){
                    //dodaj hranu u ovaj td
                    td.appendChild(createFood())
                }
            }
            row.appendChild(td)
        }
        table.appendChild(row)
    }
    document.getElementById("game").appendChild(table)   
    localStorage.setItem("playerName", null)
    setInterval(spawnSuperFood, 10000)
    move = setInterval(moveSnake, speed, "down")
    localStorage.setItem("lastPlayer", null)
    printResaults()
}

function createFood(){
    food = document.createElement("span")
    food.setAttribute("id", "food")
    food.style.cssText = "width:30px; height:30px; background-color: rgba(212, 0, 51, 1); border-radius: 50%; display: block;"
    return food
}

function createSuperFood(){
    superFood = document.createElement("span")
    superFood.setAttribute("id", "superFood")
    superFood.style.cssText = "width:30px; height:30px; background-color: green; border-radius: 50%; display: block;"
    return superFood
}

function printResaults(){
    $("#current_resault").html(localStorage.getItem("currentResault"))
    $("#best_resault").html(localStorage.getItem("bestResault"))
}

function moveSnake(way){
    size = parseInt(localStorage.getItem("size"))
    field = JSON.parse(localStorage.getItem("field"))
    curr = JSON.parse(localStorage.getItem("snake"))
    currentResault = parseInt(localStorage.getItem("currentResault"))

    if(way == "left"){
        newX = curr.x
        newY = curr.y - 1
    }else if(way == "right"){
        newX = curr.x
        newY = curr.y + 1
    }else if(way == "up"){
        newX = curr.x - 1
        newY = curr.y
    }else if(way == "down"){
        newX = curr.x + 1
        newY = curr.y
    }else return false

    if(newX < 0 || newY < 0 || newX >= size || newY >=size){
        //udarili smo u ivicu
        saveResault()
        return false
    }else if(field[newX][newY] == 0){
        //prazno polje na koje se pomeramo
        //pomeramo glavu prvo
        node = {
            x: newX,
            y: newY,
            next: curr
        }
        field[newX][newY] = 1

        //ako je samo jedan node
        if(curr.next == null){
            //brisem odmah taj jedan
            node.next = null
            field[curr.x][curr.y] = 0
            localStorage.setItem("snake", JSON.stringify(node))
            localStorage.setItem("field", JSON.stringify(field))
            refreshTable()
            return true
        }
        //ako ima vise nodova
        //pomeram se na predposlenji node
        while(curr.next.next != null){
            curr = curr.next
        }
        //brisem poslenji node
        field[curr.next.x][curr.next.y] = 0
        curr.next = null
        localStorage.setItem("snake", JSON.stringify(node))
        localStorage.setItem("field", JSON.stringify(field))
        refreshTable()
        return true
    }else if(field[newX][newY] == 1){
        //udarili smo u samog sebe
        saveResault()
        return false
    }else if(field[newX][newY] == 2 || field[newX][newY] == 3){
        //hrana
        if(field[newX][newY] == 2){
            currentResault++
            $("#food").remove()

            //generisemo novu hranu
            while(true){
                row = Math.floor(Math.random() * size)
                col = Math.floor(Math.random() * size)
                if(field[row][col] != 1 && field[row][col] != 3){
                    field[row][col] = 2
                    break;
                }
            }
            $("#"+row+"-"+col).html(createFood())
        }
        
        if(field[newX][newY] == 3){
            currentResault+=10
            $("#superFood").remove()
        }
        
        field[newX][newY] = 1
        node = {
            x: newX,
            y: newY,
            next: curr
        }


        localStorage.setItem("currentResault", currentResault)
        printResaults()
        localStorage.setItem("snake", JSON.stringify(node))
        localStorage.setItem("field", JSON.stringify(field))
        refreshTable()
        return true
    }else return false
}

function refreshTable(){
    size = parseInt(localStorage.getItem("size"))
    field = JSON.parse(localStorage.getItem("field"))

    for(i = 0; i < size; i++){
        for(j = 0; j < size; j++){
            if(field[i][j] == 0 || field[i][j] == 2 || field[i][j] == 3){
                if(i%2 == 1){
                    if(j%2==1)
                        $("#"+i+"-"+j).css("background-color", "RGB(52, 58, 64)")
                    else
                        $("#"+i+"-"+j).css("background-color", "rgba(43, 43, 43, 1)")
                }else{
                    if(j%2==0)
                        $("#"+i+"-"+j).css("background-color", "RGB(52, 58, 64)")
                    else
                        $("#"+i+"-"+j).css("background-color", "rgba(43, 43, 43, 1)")
                }
            }else if(field[i][j] == 1){
                $("#"+i+"-"+j).css("background-color", "rgba(0, 61, 219, 1)")
            }
        }
    }
}

function saveResault(){
    playerName = localStorage.getItem("playerName")

    if(playerName != "null") return
    playerName = prompt("Vase ime?")
    localStorage.setItem("playerName", playerName)
    if(playerName == null)
        window.open("zmijica-rezultati.html", "_self")
    leaderboard = JSON.parse(localStorage.getItem("leaderboard"))
    currentResault = parseInt(localStorage.getItem("currentResault"))
    bestResault = parseInt(localStorage.getItem("bestResault"))
    player = {
        name: playerName,
        score: currentResault
    }
    leaderboard.push(player)
    localStorage.setItem("lastPlayer", JSON.stringify(player))
    localStorage.setItem("leaderboard", JSON.stringify(leaderboard))
    localStorage.setItem("currentResault", 0)
    if(currentResault > bestResault){
        localStorage.setItem("bestResault", currentResault)
    }
    window.open("zmijica-rezultati.html", "_self")
}

function printLeaderboard(){
    leaderboard = JSON.parse(localStorage.getItem("leaderboard"))
    table = document.createElement("table")
    table.className = "table table-bordered table-dark table-striped"
    row = document.createElement("tr")
    
    th = document.createElement("th")
    th.innerHTML = "#"
    row.appendChild(th)
    th = document.createElement("th")
    th.innerHTML = "Name"
    row.appendChild(th)
    th = document.createElement("th")
    th.innerHTML = "Score"
    row.appendChild(th)
    table.appendChild(row)
    
    leaderboard.sort((a, b) => {
        if(parseInt(a.score) > parseInt(b.score))
            return -1
    })

    for(let i = 0; i < leaderboard.length && i < 5; i++){
        row = document.createElement("tr")

        td = document.createElement("td")
        td.innerHTML = i + 1
        row.appendChild(td)

        td = document.createElement("td")
        td.innerHTML = leaderboard[i].name
        row.appendChild(td)

        td = document.createElement("td")
        td.innerHTML = leaderboard[i].score
        row.appendChild(td)
        
        table.appendChild(row)
    }
    
    lastPlayer = JSON.parse(localStorage.getItem("lastPlayer"))
    if(lastPlayer != null){
        row = document.createElement("tr")

        td = document.createElement("td")
        td.innerHTML = "Your score this round: "
        row.appendChild(td)
    
        td = document.createElement("td")
        td.innerHTML = lastPlayer.name
        row.appendChild(td)
    
        td = document.createElement("td")
        td.innerHTML = lastPlayer.score
        row.appendChild(td)
        
        table.appendChild(row)
    }
    

    document.getElementById("leaderboard").appendChild(table)
}

function spawnSuperFood(){
    field = JSON.parse(localStorage.getItem("field"))

    //trazimo slobodnu poziciju
    while(true){
        row = Math.floor(Math.random() * size)
        col = Math.floor(Math.random() * size)
        if(field[row][col] != 1 && field[row][col] != 2){
            field[row][col] = 3
            break;
        }
    }
    $("#"+row+"-"+col).html(createSuperFood())
    localStorage.setItem("field", JSON.stringify(field))
    setTimeout(despawnSuperFood, 4000)
}

function despawnSuperFood(){
    field = JSON.parse(localStorage.getItem("field"))
    for(i = 0; i < size; i++){
        for(j = 0; j < size; j++){
            if(field[i][j] == 3){
                field[i][j] = 0
                $("#superFood").remove()
            }
        }
    }
    localStorage.setItem("field", JSON.stringify(field))
}