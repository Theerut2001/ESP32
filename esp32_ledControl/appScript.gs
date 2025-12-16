function doGet(e) {
  // เปิดใช้งาน Spreadsheet ที่กำลังทำงานอยู่
  var sheet = SpreadsheetApp.getActiveSpreadsheet().getActiveSheet();

  // อ่านค่าจากช่อง
  var value = sheet.getRange('B2').getValue();

  // สร้างเนื้อหาที่จะตอบกลับ (Text/Plain)
  return ContentService.createTextOutput(valueA1.toString())
         .setMimeType(ContentService.MimeType.TEXT);
}
