<?php
echo rate();

function rate() {
        $reply = '';
        $replyXml = file_get_contents("https://www.cbr.ru/scripts/XML_daily.asp");
        $ratesData = simplexml_load_string($replyXml);
        $currsToShow = ["USD", "EUR", ];
        foreach($ratesData->Valute as $curr) {
                if(in_array($curr->CharCode, $currsToShow)) {
                        if($reply) {
                                $reply .= "; ";
                        }
                        $charCode = $curr->CharCode;
                        $value = $curr->Value;
                        $nominal = $curr->Nominal;
                        if($nominal == 1) $rate = $value;
                        else $rate = "$value/$nominal";
                        $reply .= "$charCode $rate";
                }
        }
        return $reply;
}
