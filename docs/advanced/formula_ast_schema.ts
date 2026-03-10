export type FormulaExpressionObj = UnaryExpressionObj | BinaryExpressionObj | ConditionExpressionObj | ConstantExpressionObj |
    ConvertExpressionObj | DefaultExpressionObj | IndexExpressionObj | InvokeExpressionObj | LambdaExpressionObj | MemberExpressionObj |
    NewArrayBoundExpressionObj | NewArrayInitExpressionObj | ListInitExpressionObj | MemberInitExpressionObj | NewExpressionObj |
    TypeIsExpressionObj | TypeOfExpressionObj;

export interface UnaryExpressionObj {
    'expressionType': 'UncheckedScope' | 'CheckedScope' | 'Group' | 'UnaryPlus' | 'Negate' | 'NegateChecked' | 'Not' | 'Complement';
    'expression': FormulaExpressionObj;
}

export interface BinaryExpressionObj {
    'expressionType': 'Divide' | 'MultiplyChecked' | 'Multiply' | 'Power' | 'Modulo' | 'AddChecked' | 'Add' | 'SubtractChecked' | 'Subtract' | 'LeftShift' | 'RightShift' | 'GreaterThan' | 'GreaterThanOrEqual' | 'LessThan' | 'LessThanOrEqual' | 'Equal' | 'NotEqual' | 'And' | 'Or' | 'ExclusiveOr' | 'AndAlso' | 'OrElse' | 'Coalesce';
    'left': FormulaExpressionObj;
    'right': FormulaExpressionObj;
};

export interface ConditionExpressionObj {
    'expressionType': 'Condition';
    'test': FormulaExpressionObj;
    'ifTrue': FormulaExpressionObj;
    'ifFalse': FormulaExpressionObj;
}

export interface ConstantExpressionObj {
    'expressionType': 'Constant';
    'type': TypeReferenceObj | string;
    'value': any;
};

export interface ConvertExpressionObj {
    'expressionType': 'TypeAs' | 'Convert' | 'ConvertChecked';
    'type': TypeReferenceObj | string;
    'expression': FormulaExpressionObj;
}

export interface DefaultExpressionObj {
    'expressionType': 'Default';
    'type': TypeReferenceObj | string;
}

export interface IndexExpressionObj {
    'expressionType': 'Index';
    'expression': FormulaExpressionObj;
    'arguments': ArgumentCollectionObj;
    'useNullPropagation': boolean;
}


export interface InvokeExpressionObj {
    'expressionType': 'Invoke';
    'expression': FormulaExpressionObj;
    'arguments': ArgumentCollectionObj;
}

export interface LambdaExpressionObj {
    'expressionType': 'Lambda';
    'arguments': ArgumentCollectionObj;
    'expression': FormulaExpressionObj;
}

export interface MemberExpressionObj {
    'expressionType': 'MemberResolve';
    'name': string;
    'arguments'?: TypeArgumentCollectionObj;
    'expression'?: FormulaExpressionObj | null;
    'useNullPropagation': boolean;
};

export interface NewArrayBoundExpressionObj {
    'expressionType': 'NewArrayBounds';
    'type': TypeReferenceObj | string;
    'arguments': ArgumentCollectionObj;
};

export interface NewArrayInitExpressionObj {
    'expressionType': 'NewArrayInit';
    'type': TypeReferenceObj | string;
    'initializers': ArgumentCollectionObj;
};

export interface ListInitExpressionObj {
    'expressionType': 'ListInit';
    'new': NewExpressionObj;
    'initializers': ElementInitCollectionObj;
};

export interface MemberInitExpressionObj {
    'expressionType': 'MemberInit';
    'new': NewExpressionObj;
    'bindings': MemberBindingCollectionObj;
};

export interface NewExpressionObj {
    'expressionType': 'New';
    'type': TypeReferenceObj | string;
    'arguments': ArgumentCollectionObj;
}

export interface TypeIsExpressionObj {
    'expressionType': 'TypeIs';
    'type': TypeReferenceObj | string;
    'expression': FormulaExpressionObj;
}

export interface TypeOfExpressionObj {
    'expressionType': 'TypeOf';
    'type': TypeReferenceObj | string;
}

export interface TypeReferenceObj {
    'name': string;
    'expressionType'?: 'MemberResolve';
    'expression'?: TypeReferenceObj | string;
    'arguments'?: TypeArgumentCollectionObj;
}

export interface ElementInitBindingObj {
    'expressionType': 'ElementInitBinding';
    'initializers': ArgumentCollectionObj;
}

export interface MemberMemberBindingObj {
    'expressionType': 'MemberBinding';
    'name': string;
    'bindings': MemberBindingCollectionObj;
}

export interface MemberListBindingObj {
    'expressionType': 'ListBinding';
    'name': string;
    'initializers': ElementInitCollectionObj;
}

export interface MemberAssignmentBindingObj {
    'expressionType': 'AssignmentBinding';
    'name': string;
    'expression': FormulaExpressionObj;
}

export interface TypeArgumentCollectionObj {
    [name: string]: TypeReferenceObj | string;
}

export interface ArgumentCollectionObj {
    [name: string]: FormulaExpressionObj | null;
}

export interface ElementInitCollectionObj {
    [name: string]: ElementInitBindingObj;
}

export interface MemberBindingCollectionObj {
    [name: string]: MemberMemberBindingObj | MemberListBindingObj | MemberAssignmentBindingObj;
}
