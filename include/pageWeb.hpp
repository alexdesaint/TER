const char MAIN_page[] = R"=====(
<meta http-equiv="Content-type" content="text/html; charset=utf-8">
<meta name="viewport" content="width=device-width,initial-scale=1,user-scalable=no">
<title>DataTables example - HTML5 export buttons</title>
<link rel="stylesheet" type="text/css" href="jquery.dataTables.min.css">
<link rel="stylesheet" type="text/css" href="buttons.dataTables.min.css">

<script type="text/javascript" language="javascript" src="jquery-3.3.1.js"></script>
<script type="text/javascript" language="javascript" src="jquery.dataTables.min.js"></script>
<script type="text/javascript" language="javascript" src="dataTables.buttons.min.js"></script>
<script type="text/javascript" language="javascript" src="jszip.min.js"></script>
<script type="text/javascript" language="javascript" src="pdfmake.min.js"></script>
<script type="text/javascript" language="javascript" src="vfs_fonts.js"></script>
<script type="text/javascript" language="javascript" src="buttons.html5.min.js"></script>
<script type="text/javascript" class="init">
    $(document).ready(function () {
        $('#example').DataTable({
            dom: 'Bfrtip',
            buttons: [
                'copyHtml5',
                'excelHtml5',
                'csvHtml5',
                'pdfHtml5'
            ]
        });
    });
</script>

<table id="example" class="display dataTable" style="width:100%" role="grid" aria-describedby="example_info">
    <thead>
        <tr role="row">
            <th class="sorting_asc" tabindex="0" aria-controls="example" rowspan="1" colspan="1" style="width: 128.867px;"
                aria-sort="ascending" aria-label="Name: activate to sort column descending">Name</th>
            <th class="sorting" tabindex="0" aria-controls="example" rowspan="1" colspan="1" style="width: 217.267px;"
                aria-label="Position: activate to sort column ascending">Position</th>
            <th class="sorting" tabindex="0" aria-controls="example" rowspan="1" colspan="1" style="width: 96.6px;"
                aria-label="Office: activate to sort column ascending">Office</th>
            <th class="sorting" tabindex="0" aria-controls="example" rowspan="1" colspan="1" style="width: 39.2667px;"
                aria-label="Age: activate to sort column ascending">Age</th>
            <th class="sorting" tabindex="0" aria-controls="example" rowspan="1" colspan="1" style="width: 88.25px;"
                aria-label="Start date: activate to sort column ascending">Start date</th>
            <th class="sorting" tabindex="0" aria-controls="example" rowspan="1" colspan="1" style="width: 73.9px;"
                aria-label="Salary: activate to sort column ascending">Salary</th>
        </tr>
    </thead>
    <tbody>
        <tr role="row" class="odd">
            <td class="sorting_1">Airi Satou</td>
            <td>Accountant</td>
            <td>Tokyo</td>
            <td>33</td>
            <td>2008/11/28</td>
            <td>$162,700</td>
        </tr>
        <tr role="row" class="even">
            <td class="sorting_1">Angelica Ramos</td>
            <td>Chief Executive Officer (CEO)</td>
            <td>London</td>
            <td>47</td>
            <td>2009/10/09</td>
            <td>$1,200,000</td>
        </tr>
        <tr role="row" class="odd">
            <td class="sorting_1">Ashton Cox</td>
            <td>Junior Technical Author</td>
            <td>San Francisco</td>
            <td>66</td>
            <td>2009/01/12</td>
            <td>$86,000</td>
        </tr>
        <tr role="row" class="even">
            <td class="sorting_1">Bradley Greer</td>
            <td>Software Engineer</td>
            <td>London</td>
            <td>41</td>
            <td>2012/10/13</td>
            <td>$132,000</td>
        </tr>
        <tr role="row" class="odd">
            <td class="sorting_1">Brenden Wagner</td>
            <td>Software Engineer</td>
            <td>San Francisco</td>
            <td>28</td>
            <td>2011/06/07</td>
            <td>$206,850</td>
        </tr>
        <tr role="row" class="even">
            <td class="sorting_1">Brielle Williamson</td>
            <td>Integration Specialist</td>
            <td>New York</td>
            <td>61</td>
            <td>2012/12/02</td>
            <td>$372,000</td>
        </tr>
        <tr role="row" class="odd">
            <td class="sorting_1">Bruno Nash</td>
            <td>Software Engineer</td>
            <td>London</td>
            <td>38</td>
            <td>2011/05/03</td>
            <td>$163,500</td>
        </tr>
        <tr role="row" class="even">
            <td class="sorting_1">Caesar Vance</td>
            <td>Pre-Sales Support</td>
            <td>New York</td>
            <td>21</td>
            <td>2011/12/12</td>
            <td>$106,450</td>
        </tr>
        <tr role="row" class="odd">
            <td class="sorting_1">Cara Stevens</td>
            <td>Sales Assistant</td>
            <td>New York</td>
            <td>46</td>
            <td>2011/12/06</td>
            <td>$145,600</td>
        </tr>
        <tr role="row" class="even">
            <td class="sorting_1">Cedric Kelly</td>
            <td>Senior Javascript Developer</td>
            <td>Edinburgh</td>
            <td>22</td>
            <td>2012/03/29</td>
            <td>$433,060</td>
        </tr>
    </tbody>
</table>
)=====";
