using System;

public class CodeGenerator
{
    public static string GenerateProperty(string fieldName, string propertyName, string typeName)
    {
        return $@"
            [SerializeField] private {typeName} {fieldName};

            public {typeName} {propertyName}
            {{
                get {{ return {fieldName}; }}
                set {{ {fieldName} = value; }}
            }}";
    }

    public static string GenerateReadOnlyString(string fieldName)
    {
        return $"public static readonly string {fieldName} = nameof({fieldName});";
    }
}

public class YourClass
{
    // 사용 예시
    public static void Main()
    {
        Console.WriteLine(CodeGenerator.GenerateProperty("canvas", "Canvas", "CanvasType"));
        Console.WriteLine(CodeGenerator.GenerateReadOnlyString("canvas"));
    }
}

public class CanvasType
{
    // CanvasType의 내용
}