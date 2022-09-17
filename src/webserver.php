<?php header('Access-Control-Allow-Origin: *'); ?>
<?php

//Vars
$pathGamefile = 'C:\Program Files\xampp\htdocs\game\game.txt';


//Spielarray-Datei erzeugen
if(!file_exists($pathGamefile)){
    $spielArray=array();
    for($i=0 ; $i<=24 ; $i++){
        $spielArray[$i] = intval(0);
    }
    file_put_contents($pathGamefile,serialize($spielArray));
}else{
    $spielArray = unserialize(file_get_contents($pathGamefile));
}


if(isset($_GET['added']) && isset($_GET['removed'])){
    //Falls Formular benutzt wurde
    if(isset($_GET['send'])){

    }
    $spielArray[$_GET['added']] = intval(1);
    $spielArray[$_GET['removed']] = intval(0);
    file_put_contents($pathGamefile,serialize($spielArray));
}else{
    //Wenn Spielstein hinzugefügt
    if(isset($_GET['added'])){
        $spielArray[$_GET['added']] = intval(1);
        file_put_contents($pathGamefile,serialize($spielArray));
    }
    if(isset($_POST['added'])){
        $spielArray[$_POST['added']] = intval(1);
        file_put_contents($pathGamefile,serialize($spielArray));
    }
    //Wenn Spielstein entfernt
    if(isset($_GET['removed'])){
        $spielArray[$_GET['removed']] = intval(0);
        file_put_contents($pathGamefile,serialize($spielArray));
    }
    if(isset($_POST['removed'])){
        $spielArray[$_POST['removed']] = intval(0);
        file_put_contents($pathGamefile,serialize($spielArray));
    }
}

?>
<?php if(!isset($_GET['hidden']) && !(isset($_GET['added']) || isset($_GET['removed']))) :?>
    <html>
        <meta http-equiv="refresh" content="10" >
        <link rel="stylesheet" href="https://cdn.jsdelivr.net/npm/bootstrap@4.3.1/dist/css/bootstrap.min.css" integrity="sha384-ggOyR0iXCbMQv3Xipma34MD+dH/1fQ784/j6cY/iJTQUOhcWr7x9JvoRxT2MZw1T" crossorigin="anonymous">
        <script src="https://code.jquery.com/jquery-3.3.1.slim.min.js" integrity="sha384-q8i/X+965DzO0rT7abK41JStQIAqVgRVzpbzo5smXKp4YfRvH+8abtTE1Pi6jizo" crossorigin="anonymous"></script>
        <script src="https://cdn.jsdelivr.net/npm/popper.js@1.14.7/dist/umd/popper.min.js" integrity="sha384-UO2eT0CpHqdSJQ6hJty5KVphtPhzWj9WO1clHTMGa3JDZwrnQq4sF86dIHNDz0W1" crossorigin="anonymous"></script>
        <script src="https://cdn.jsdelivr.net/npm/bootstrap@4.3.1/dist/js/bootstrap.min.js" integrity="sha384-JjSmVgyd0p3pXB1rRibZUAYoIIy6OrQ6VrjIEaFf/nJGzIxFDsf4x0xIM+B07jRM" crossorigin="anonymous"></script>
        <script src="https://ajax.googleapis.com/ajax/libs/jquery/3.6.0/jquery.min.js"></script>

        <!--Hier kommt das Spielfeld Hin-->
        <div class="container-fluid">
            <table class="table table-bordered">
                <tr>
                    <td <?=$spielArray[1] == intval(1)? 'class="table-dark"' : ''?>><center><?=$spielArray[1] == intval(1)? '<button type="button" class="btn btn-danger" id="remove_1" type="button" data-value1="1">' : '<button type="button" class="btn btn-success" id="add_1" type="button" data-value1="1">'?>1</button> </center></td>
                    <td></td>
                    <td></td>
                    <td <?=$spielArray[2] == intval(1)? 'class="table-dark"' : ''?>><center><?=$spielArray[2] == intval(1)? '<button type="button" class="btn btn-danger" id="remove_2" type="button" data-value1="2">' : '<button type="button" class="btn btn-success" id="add_2" type="button" data-value1="2">'?>2</button> </center></td>
                    <td></td>
                    <td></td>
                    <td <?=$spielArray[3] == intval(1)? 'class="table-dark"' : ''?>><center><?=$spielArray[3] == intval(1)? '<button type="button" class="btn btn-danger" id="remove_3" type="button" data-value1="3">' : '<button type="button" class="btn btn-success" id="add_3" type="button" data-value1="3">'?>3</button> </center></td>
                </tr>
                <tr>
                    <td></td>
                    <td <?=$spielArray[4] == intval(1)? 'class="table-dark"' : ''?>><center><?=$spielArray[4] == intval(1)? '<button type="button" class="btn btn-danger" id="remove_4" type="button" data-value1="4">' : '<button type="button" class="btn btn-success" id="add_4" type="button" data-value1="4">'?>4</button> </center></td>
                    <td></td>
                    <td <?=$spielArray[5] == intval(1)? 'class="table-dark"' : ''?>><center><?=$spielArray[5] == intval(1)? '<button type="button" class="btn btn-danger" id="remove_5" type="button" data-value1="5">' : '<button type="button" class="btn btn-success" id="add_5" type="button" data-value1="5">'?>5</button> </center></td>
                    <td></td>
                    <td <?=$spielArray[6] == intval(1)? 'class="table-dark"' : ''?>><center><?=$spielArray[6] == intval(1)? '<button type="button" class="btn btn-danger" id="remove_6" type="button" data-value1="6">' : '<button type="button" class="btn btn-success" id="add_6" type="button" data-value1="6">'?>6</button> </center></td>
                    <td></td>
                </tr>
                <tr>
                    <td></td>
                    <td></td>
                    <td <?=$spielArray[7] == intval(1)? 'class="table-dark"' : ''?>><center><?=$spielArray[7] == intval(1)? '<button type="button" class="btn btn-danger" id="remove_7" type="button" data-value1="7">' : '<button type="button" class="btn btn-success" id="add_7" type="button" data-value1="7">'?>7</button> </center></td>
                    <td <?=$spielArray[8] == intval(1)? 'class="table-dark"' : ''?>><center><?=$spielArray[8] == intval(1)? '<button type="button" class="btn btn-danger" id="remove_8" type="button" data-value1="8">' : '<button type="button" class="btn btn-success" id="add_8" type="button" data-value1="8">'?>8</button> </center></td>
                    <td <?=$spielArray[9] == intval(1)? 'class="table-dark"' : ''?>><center><?=$spielArray[9] == intval(1)? '<button type="button" class="btn btn-danger" id="remove_9" type="button" data-value1="9">' : '<button type="button" class="btn btn-success" id="add_9" type="button" data-value1="9">'?>9</button> </center></td>
                    <td></td>
                    <td></td>
                </tr>
                <tr>
                    <td <?=$spielArray[10] == intval(1)? 'class="table-dark"' : ''?>><center><?=$spielArray[10] == intval(1)? '<button type="button" class="btn btn-danger" id="remove_10" type="button" data-value1="10">' : '<button type="button" class="btn btn-success" id="add_10" type="button" data-value1="10">'?>10</button> </center></td>
                    <td <?=$spielArray[11] == intval(1)? 'class="table-dark"' : ''?>><center><?=$spielArray[11] == intval(1)? '<button type="button" class="btn btn-danger" id="remove_11" type="button" data-value1="11">' : '<button type="button" class="btn btn-success" id="add_11" type="button" data-value1="11">'?>11</button> </center></td>
                    <td <?=$spielArray[12] == intval(1)? 'class="table-dark"' : ''?>><center><?=$spielArray[12] == intval(1)? '<button type="button" class="btn btn-danger" id="remove_12" type="button" data-value1="12">' : '<button type="button" class="btn btn-success" id="add_12" type="button" data-value1="12">'?>12</button> </center></td>
                    <td <?=$spielArray[0] == intval(1)? 'class="table-dark"' : ''?>><center><?=$spielArray[0] == intval(1)? '<button type="button" class="btn btn-danger" id="remove_0" type="button" data-value1="0">' : '<button type="button" class="btn btn-success" id="add_0" type="button" data-value1="0">'?>0</button> </center></td>
                    <td <?=$spielArray[13] == intval(1)? 'class="table-dark"' : ''?>><center><?=$spielArray[13] == intval(1)? '<button type="button" class="btn btn-danger" id="remove_13" type="button" data-value1="13">' : '<button type="button" class="btn btn-success" id="add_13" type="button" data-value1="13">'?>13</button> </center></td>
                    <td <?=$spielArray[14] == intval(1)? 'class="table-dark"' : ''?>><center><?=$spielArray[14] == intval(1)? '<button type="button" class="btn btn-danger" id="remove_14" type="button" data-value1="14">' : '<button type="button" class="btn btn-success" id="add_14" type="button" data-value1="14">'?>14</button> </center></td>
                    <td <?=$spielArray[15] == intval(1)? 'class="table-dark"' : ''?>><center><?=$spielArray[15] == intval(1)? '<button type="button" class="btn btn-danger" id="remove_15" type="button" data-value1="15">' : '<button type="button" class="btn btn-success" id="add_15" type="button" data-value1="15">'?>15</button> </center></td>
                </tr>
                <tr>
                    <td></td>
                    <td></td>
                    <td <?=$spielArray[16] == intval(1)? 'class="table-dark"' : ''?>><center><?=$spielArray[16] == intval(1)? '<button type="button" class="btn btn-danger" id="remove_16" type="button" data-value1="16">' : '<button type="button" class="btn btn-success" id="add_16" type="button" data-value1="16">'?>16</button> </center></td>
                    <td <?=$spielArray[17] == intval(1)? 'class="table-dark"' : ''?>><center><?=$spielArray[17] == intval(1)? '<button type="button" class="btn btn-danger" id="remove_17" type="button" data-value1="17">' : '<button type="button" class="btn btn-success" id="add_17" type="button" data-value1="17">'?>17</button> </center></td>
                    <td <?=$spielArray[18] == intval(1)? 'class="table-dark"' : ''?>><center><?=$spielArray[18] == intval(1)? '<button type="button" class="btn btn-danger" id="remove_18" type="button" data-value1="18">' : '<button type="button" class="btn btn-success" id="add_18" type="button" data-value1="18">'?>18</button> </center></td>
                    <td></td>
                    <td></td>
                </tr>
                <tr>
                    <td></td>
                    <td <?=$spielArray[19] == intval(1)? 'class="table-dark"' : ''?>><center><?=$spielArray[19] == intval(1)? '<button type="button" class="btn btn-danger" id="remove_19" type="button" data-value1="19">' : '<button type="button" class="btn btn-success" id="add_19" type="button" data-value1="19">'?>19</button> </center></td>
                    <td></td>
                    <td <?=$spielArray[20] == intval(1)? 'class="table-dark"' : ''?>><center><?=$spielArray[20] == intval(1)? '<button type="button" class="btn btn-danger" id="remove_20" type="button" data-value1="20">' : '<button type="button" class="btn btn-success" id="add_20" type="button" data-value1="20">'?>20</button> </center></td>
                    <td></td>
                    <td <?=$spielArray[21] == intval(1)? 'class="table-dark"' : ''?>><center><?=$spielArray[21] == intval(1)? '<button type="button" class="btn btn-danger" id="remove_21" type="button" data-value1="21">' : '<button type="button" class="btn btn-success" id="add_21" type="button" data-value1="21">'?>21</button> </center></td>
                    <td></td>
                </tr>
                <tr>
                    <td <?=$spielArray[22] == intval(1)? 'class="table-dark"' : ''?>><center><?=$spielArray[22] == intval(1)? '<button type="button" class="btn btn-danger" id="remove_22" type="button" data-value1="22">' : '<button type="button" class="btn btn-success" id="add_22" type="button" data-value1="22">'?>22</button> </center></td>
                    <td></td>
                    <td></td>
                    <td <?=$spielArray[23] == intval(1)? 'class="table-dark"' : ''?>><center><?=$spielArray[23] == intval(1)? '<button type="button" class="btn btn-danger" id="remove_23" type="button" data-value1="23">' : '<button type="button" class="btn btn-success" id="add_23" type="button" data-value1="23">'?>23</button> </center></td>
                    <td></td>
                    <td></td>
                    <td <?=$spielArray[24] == intval(1)? 'class="table-dark"' : ''?>><center><?=$spielArray[24] == intval(1)? '<button type="button" class="btn btn-danger" id="remove_24" type="button" data-value1="24">' : '<button type="button" class="btn btn-success" id="add_24" type="button" data-value1="24">'?>24</button> </center></td>
                </tr>
            </table>
            <hr>
            <form method="get" action="" id="moveForm">
                <div class="row">
                    <input type="hidden" name="send" value="1">
                    <div class="col-auto">
                        <label for="von" class="form-label">Von Position:</label>
                        <input type="number" min="0" max ="24" class="form-control" id="removed" name="removed">
                    </div>
                    <div class="col-auto">
                        <label for="nach" class="form-label">Nach Position:</label>
                        <input type="number" min="0" max ="24" class="form-control" id="added"  name="added">
                    </div>
                    <div class="col-auto">
                        <input type="submit" class="btn btn-primary">
                    </div>
                </div>
            </form>
            <hr>
            Spielfeld wird alle 10 Sekunden automatisch aktualisiert...
        </div>
        
        <script>
            $(document).ready(function(){
                $("#moveForm").submit(function(e){
                    e.preventDefault();
                    console.log('http://192.168.250.78/game/index.php?' + $("#moveForm").serialize());
                    $.get('http://192.168.250.78/game/index.php?' + $("#moveForm").serialize(),function(data, status){
                            alert("Data: " + data + "\nStatus: " + status);
                        });
                    $.post('http://localhost/game/index.php?hidden=1',{
                        added: document.getElementById('added').value,
                        removed: document.getElementById('removed').value
                    })
                    .done(function(data) {
                        //location.reload();
                    });
                })
                <?php foreach($spielArray as $key => $entry) :?>
                    $('#add_<?=$key?>').on('click', function(e) {
                        var added = String(document.getElementById('add_<?=$key?>').dataset.value1);
                        console.log('http://192.168.250.78/game/index.php?added=' + added);
                        $.get('http://192.168.250.78/game/index.php?added=' + added, function(data, status){
                            alert("Data: " + data + "\nStatus: " + status);
                        });
                        $.post('/game/index.php?hidden=1', {
                            added: added
                        })
                        .done(function(data) {
                            //location.reload();
                        });
                    });
                    $('#remove_<?=$key?>').on('click', function(e) {
                        var removed = String(document.getElementById('remove_<?=$key?>').dataset.value1);
                        console.log('http://192.168.250.78/game/index.php?removed=' + removed);
						$.get('http://192.168.250.78/game/index.php?removed=' + removed, function(data, status){
                            alert("Data: " + data + "\nStatus: " + status);
                        });
                        $.post('/game/index.php?hidden=1', {
                            removed: removed
                        })
                        .done(function(data) {
                            //location.reload();
                        });
                    });
                <?php endforeach;?>
            });
        </script>
    </html>
<?php endif;?>

<?=isset($_GET['added']) || isset($_GET['removed']) ? 'ok' : ''?>