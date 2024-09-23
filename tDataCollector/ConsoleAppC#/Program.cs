using System;
using HtmlAgilityPack;
using Microsoft.Data.Sqlite;
using SQLitePCL;
class Program
{
    static async Task Main(string[] args)
    {
        string rootUrl = "https://terraria.wiki.gg";

        SQLitePCL.Batteries_V2.Init();
        // 指定数据库文件路径
        string projectPath = Directory.GetCurrentDirectory();
        Console.WriteLine(projectPath);

        var connectionString = projectPath+"\\tDataCollector.db";

        // 创建数据库连接
        using (var connection = new SqliteConnection(connectionString))
        {
            connection.Open();

            // 创建表
            var createTableCmd = connection.CreateCommand();
            createTableCmd.CommandText =
            @"
                CREATE TABLE IF NOT EXISTS Item (
                    Id INTEGER NOT NULL PRIMARY KEY,
                    Name TEXT,
                    Chn_Name Text,
                    Chn_Url Text,
                    Eng_Name Text,
                    Eng_Url Text
                )
            ";
            createTableCmd.ExecuteNonQuery();





            var html = @"https://terraria.wiki.gg/zh/wiki/%E7%89%A9%E5%93%81_ID";

            HtmlWeb web = new HtmlWeb();

            var htmlDoc = web.Load(html);

            var table = htmlDoc.DocumentNode.SelectSingleNode("/html/body/div[3]/div[2]/div/main/div[3]/div[5]/div[1]/table");

            if (table != null)
            {

                var rows = table.SelectNodes(".//tr");

                foreach (var row in rows)
                {
                    var cells = row.SelectNodes(".//td");
                    string id = "";
                    string name = "";
                    string chn_name = "";
                    string chn_url = "";
                    if (cells != null)
                    {
                        foreach (var cell in cells)
                        {
                            if (cells.IndexOf(cell) == 0) { id = cell.InnerText; }
                            else if (cells.IndexOf(cell) == 1)
                            {
                                chn_name = cell.InnerText;
                                var url = cell.SelectSingleNode(".//a");
                                // Console.Write(url.InnerText);
                                if (url == null) { continue; }
                                // 获取href属性
                                var hrefValue = url.GetAttributeValue("href", string.Empty);
                                // 检查href是否不为空
                                if (!string.IsNullOrEmpty(hrefValue))
                                {
                                    chn_url = rootUrl + hrefValue;
                                }
                            }
                            else if (cells.IndexOf(cell) == 2) { name = cell.InnerText; }
                        }
                        // 插入数据
                        var insertCmd = connection.CreateCommand();
                        insertCmd.CommandText =
                        @"
                INSERT INTO Item (Id, Name,Chn_Name,Chn_Url)
                VALUES ($id, $name,$chn_name,$chn_url)
            ";
                        insertCmd.Parameters.AddWithValue("$id", id);
                        insertCmd.Parameters.AddWithValue("$name", name);
                        insertCmd.Parameters.AddWithValue("$chn_name", chn_name);
                        insertCmd.Parameters.AddWithValue("$chn_url", chn_url);
                        if (insertCmd.ExecuteNonQuery() == -1)
                        {
                            Console.WriteLine($"Id: {id}, Name: {name}, ChnName: {chn_name}, ChnUrl: {chn_url}");
                        }

                    }

                }
            }

            // 关闭连接
            connection.Close();
        }
    }
}